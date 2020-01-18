/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FollowTargetTillStopped2.h"
#include "Robot.h"
#include "RobotMap.h"
#include "detection/TargetDetection.h"

// Constructor - approach target
FollowTargetTilStopped2::FollowTargetTilStopped2(float Speed, bool Pickup) {
  
  // This command requires use of robot drive
  Requires (&Robot::m_MainDrive);

  // distance drive command is not interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);

  m_Speed = 60.0; // Speed;
  m_Pickup = Pickup;
}

// Called just before this Command runs the first time
void FollowTargetTilStopped2::Initialize() {
  // initially assume we are not yet arrived at target
  m_AtTarget = false;

  // type of target we are pursuing
  //m_TargetType = Robot::m_Limelight.GetPipeline();

  m_Timer1 = 0.0;

  m_LastAccelX = 0; //Robot::m_NavX.GetAccelX();;
  m_LastAccelY = 0; //Robot::m_NavX.GetAccelY();;
  m_CollisionDetected = false;

  // zero integrated error
  m_IntegratedError = 0;

  m_OldSpeed = 0.5*(Robot::m_MainDrive.GetLeftEncoderSpeed() + Robot::m_MainDrive.GetRightEncoderSpeed());
  m_CurrentSpeed = m_OldSpeed;

  m_AngleIntegratedError = 0.0;
  m_PreviousAngle = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void FollowTargetTilStopped2::Execute() {

  // get ball target information
  TARGET_DATA target = GetTargetEstimation();

  

  // determine reference speed
  float referenceSpeed = 10.0; // 2.0; // 10.0;
  
  float distance = target.ZDistance;
  if (m_Pickup && (distance > 16.0))
    distance = distance - 16.0;
  //else if ((!m_Pickup) && (distance > 6.0))
  //  distance = distance - 6.0;

  if (target.Detected == true){
    referenceSpeed = 0.70*distance + 10.0; // 2.0; // 10.0;
  }
    
  if (referenceSpeed > m_Speed){
    referenceSpeed = m_Speed;
  }

  // determine average current speed;
  //m_CurrentSpeed = 0.9*m_CurrentSpeed + 0.1*0.5*(Robot::m_MainDrive.GetLeftEncoderSpeed() + Robot::m_MainDrive.GetRightEncoderSpeed());
  //float currentSpeed = m_CurrentSpeed;
  float currentSpeed = 0.5*(Robot::m_MainDrive.GetLeftEncoderSpeed() + Robot::m_MainDrive.GetRightEncoderSpeed());

  // determine current speed error
  float speedError = referenceSpeed - currentSpeed;

  // calculate integrated error
  m_IntegratedError = m_IntegratedError + 50.0*speedError;

  if (m_IntegratedError > 20000.0)
    m_IntegratedError = 20000.0;

  // determine differtial error
  float differentialError = 50.0*(currentSpeed - m_OldSpeed);
  m_OldSpeed = currentSpeed;

  // implement PID control
  float targetSpeed = speedError*0.01 + m_IntegratedError*0.00001; // + differentialError*0.01;

  // have we detected a ball?
  if (target.Detected == true) //- for now, pursue all targets same way
  {
    // target has been detected
  
    ///////////////////// ANGLE PID CONTROL

    // get angle to target
    float TargetAngle = target.XAngle;
    
    // integrate error - do not integrate if error is over 10 deg
  if (fabs(TargetAngle) >4.0) 
    m_AngleIntegratedError = 0;
  else
    m_AngleIntegratedError = m_AngleIntegratedError + 0.02*TargetAngle;

  // differential error
  // for speed optimization multiply instead of divicde - 1.0/0.02 = 50.0
  float AngleDifferentialError = (TargetAngle - m_PreviousAngle) * 50.0;

  m_PreviousAngle = TargetAngle;
// PI output
  double AnglePIDOutput = 0.02 * TargetAngle +0.010*AngleDifferentialError;// + 0.01*m_AngleIntegratedError; //- 0.005*AngleDifferentialError;

  /////////////////////// END ANGLE PID CONTROL

    // is angle correction positive or negative?
    if (AnglePIDOutput >=0.0)
      // drive towards target
      Robot::m_MainDrive.SetArcadeDrive(-targetSpeed, std::min(0.3, AnglePIDOutput), false);
    
    else 
      // drive towards target
      Robot::m_MainDrive.SetArcadeDrive(-targetSpeed, std::max(AnglePIDOutput, -0.3), false);
   
  }
  else
  // we don't have target - just drive straight ahead anyway
   Robot::m_MainDrive.SetArcadeDrive(-targetSpeed, 0, false);

  
  double currentAccelX =  Robot::m_NavX.GetAccelX();
  double currentJerkX = (currentAccelX - m_LastAccelX);
  m_LastAccelX = currentAccelX;
  double currentAccelY = Robot::m_NavX.GetAccelY();
  double currentJerkY = (currentAccelY - m_LastAccelY);
  m_LastAccelY = currentAccelY;

  if ( ( fabs(currentJerkX) > TARGET_COLLISION_THRESHOLD_DELTA_G ) ||
      ( fabs(currentJerkY) > TARGET_COLLISION_THRESHOLD_DELTA_G) ) {
          m_CollisionDetected = true;
  }

  if (fabs(Robot::m_MainDrive.GetLeftEncoderSpeed()) <= 0.1 && fabs(Robot::m_MainDrive.GetRightEncoderSpeed()) <= 0.1)
        m_Timer1 =m_Timer1 + 0.02;
  else
    m_Timer1 =  0.0;


}

// Return true when this Command is finished
bool FollowTargetTilStopped2::IsFinished() { 
  //float AvgDistance= 0.5 * (Robot::m_MainDrive.GetLeftEncoderDistance() + Robot::m_MainDrive.GetRightEncoderDistance());
  
  return (m_Timer1 >0.3);
  //return (m_Timer1>0.5);
  // have we travelled far enough (within 2" of target)
  //if (fabs(m_Distance-AvgDistance)< 1.0 )
  //  return true; 
  //else
  //  return false;
}

// Called once after isFinished returns true
void FollowTargetTilStopped2::End() {
    Robot::m_MainDrive.SetArcadeDrive(0.0, 0.0 , false);
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowTargetTilStopped2::Interrupted() {
  
}
