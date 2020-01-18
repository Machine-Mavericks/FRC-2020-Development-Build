/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveGoToTarget.h"
#include "detection/TargetDetection.h"
#include "Robot.h"
#include "RobotMap.h"

const float DegtoRad = kPi/180.0;
const float RadtoDeg = 180.0/kPi;


DriveGoToTarget::PATHTOTARGET tg;

// Constructor - approach target
DriveGoToTarget::DriveGoToTarget(float Speed) {
  
  // This command requires use of robot drive
  Requires (&Robot::m_MainDrive);

  // distance drive command is not interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);

  Steer = new DriveSteerTowardsTarget();

  m_Speed = Speed;
}

// Called just before this Command runs the first time
void DriveGoToTarget::Initialize() {
   
  // by default, set pointers to NULL (no instances of commands exist)
  Turn1 = NULL;
  Distance1 = NULL;
  Turn2 = NULL;
  Distance2 =NULL;

    Steer->Initialize();

    // assume we have no target lock unless proven otherwise
    m_PathToTarget.TargetLock = false;

    // get new target estimation
    TARGET_DATA target = GetTargetEstimation();

    // do we have a chevron?
    if (target.Detected && target.TargetType==0 ) // && target.ZDistance > SETBACK)
    {
      // we have a chevron target - lock on target
      m_PathToTarget.TargetLock = true;
      m_PathToTarget.TargetType = 0;

      // determine path to target
    
      // ensure we do not divide by zero
      if (target.XDistance ==0.0)
        target.XDistance = target.XDistance + 0.001; 

      float Setback = 72.0;

      // to avoid unusual turning angles, place setback further back behind robot
      if (target.ZDistance > 48.0)
        Setback = target.ZDistance + 24.0;


      // angle of vector from robot to target 
      float Angle1 = RadtoDeg*atan(target.ZDistance/target.XDistance); 

      float Angle2 = RadtoDeg*atan((Setback - target.ZDistance)/target.XDistance); 

      if (target.XDistance> 0.0)
      m_PathToTarget.Angle1 = -(180.0 - target.XAngle- Angle1 - Angle2);
      else
      m_PathToTarget.Angle1 = (180.0 + target.XAngle+ Angle1 + Angle2);

      m_PathToTarget.Distance1 = -sqrt(target.XDistance*target.XDistance+ (Setback-target.ZDistance)*(Setback-target.ZDistance));

      if (target.XDistance> 0.0)
      m_PathToTarget.Angle2 = 90.0-Angle2;
      else
      m_PathToTarget.Angle2 = -(90.0+Angle2);

      m_PathToTarget.Distance2 = Setback;

      /*            
      // angle of vector from robot to target-setback point
      float Angle2 = RadtoDeg*atan((target.ZDistance-SETBACK)/target.XDistance); 

      // Angle to turn robot by to meet target - setback
      m_PathToTarget.Angle1 = target.XAngle + (Angle1 - Angle2);

      // distance to setback point
      m_PathToTarget.Distance1 = sqrt(target.XDistance*target.XDistance+ (target.ZDistance-SETBACK)*(target.ZDistance-SETBACK));
    
      // final angle to turn towards target
      if (target.XDistance> 0.0)
       m_PathToTarget.Angle2 = -(90-Angle2);
      else 
        m_PathToTarget.Angle2 = 90+Angle2;

      // final drive towards target
      m_PathToTarget.Distance2 = SETBACK; */

      // initialize first state
      m_PathToTarget.State = 0;

      // create commands to drive towards target
      Turn1 = new DriveTurnToAngle (m_PathToTarget.Angle1,1.0, 0.5, 0.0);
      Distance1 = new DriveStraightDistance(m_PathToTarget.Distance1, 1.0, 0.25);
      Turn2 = new DriveTurnToAngle (m_PathToTarget.Angle2, 1.0, 0.5, 0.0);
      Distance2 = new DriveStraightDistance(m_PathToTarget.Distance2, 1.0, m_Speed);
     
      //////////////////////////////////////
      // temporary - copy to global variable to display on driver station
      tg = m_PathToTarget;
      tg.CX = target.XDistance;
      tg.CZ = target.ZDistance;
      tg.XA = target.XAngle;
      // end temporary
      //////////////////////////////////////

      // initialize first command
      Turn1->Initialize();
    }

}

// Called repeatedly when this Command is scheduled to run
void DriveGoToTarget::Execute() {


  if (m_PathToTarget.TargetLock)
  {
    // get angle to target - used for last approach motion to target
    TARGET_DATA target = GetTargetEstimation();
    float TargetAngle = target.XAngle;

    switch (m_PathToTarget.State)
    {
      // we are turning to point in front of target
      case 0:
        Turn1->Execute();
        if (Turn1->IsFinished())
          { Turn1->End(); m_PathToTarget.State = 1; Distance1->Initialize(); }
      break;

      // we are driving towards point in front of target
      case 1:
        Distance1->Execute();
        if (Distance1->IsFinished())
          { Distance1->End(); m_PathToTarget.State=2; Turn2->Initialize(); }
      break;

      // we are turning to face target
      case 2:
        Turn2->Execute();
        if (Turn2->IsFinished())
          { Turn2->End(); m_PathToTarget.State = 3; Distance2->Initialize(); 
          Robot::m_MainDrive.ResetLeftEncoder(); Robot::m_MainDrive.ResetRightEncoder(); }
      break;

      // we are driving up to target
      case 3:
  
        /*Distance2->Execute();
        if (Distance2->IsFinished())
          { Distance2->End(); m_PathToTarget.State = 4;} */

        // do we need to turn to angle?
        if ((TargetAngle >=0.5 || TargetAngle <=-0.5) && (TargetAngle>=-10.0) && (TargetAngle<=10.0))
          // drive towards target
          Robot::m_MainDrive.SetArcadeDrive(-m_Speed, 0.05*TargetAngle, false); 
        else
          // target is ahead of us, drive straight
          Robot::m_MainDrive.SetArcadeDrive(-m_Speed, 0.0, false);
          

        if (0.5*(Robot::m_MainDrive.GetLeftEncoderDistance()+Robot::m_MainDrive.GetRightEncoderDistance()) > (m_PathToTarget.Distance2-24))
           m_PathToTarget.State = 4;
      break;

      // we are finished - turn off drive
      case 4:
        Robot::m_MainDrive.SetArcadeDrive(0.0,0.0,false);
      break;

    }; // end switch
  } // end we have target lock
  else
    Steer->Execute();
  
}

// Return true when this Command is finished
bool DriveGoToTarget::IsFinished() { 
  if (m_PathToTarget.State == 4)
    return true;
  else
    return false;
}

// Called once after isFinished returns true
void DriveGoToTarget::End() {
  m_PathToTarget.TargetLock = false;
  
  // we are finished, delete any commands that have been created
  if (Turn1!=NULL)
    { delete Turn1; Turn1=NULL; } 
  if (Distance1!=NULL)
    { delete Distance1; Distance1=NULL; }
  if (Turn2!=NULL)
    { delete Turn2; Turn2=NULL; }
  if (Distance2!=NULL)
    { delete Distance2; Distance2=NULL; }
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveGoToTarget::Interrupted() {
  End();
}



