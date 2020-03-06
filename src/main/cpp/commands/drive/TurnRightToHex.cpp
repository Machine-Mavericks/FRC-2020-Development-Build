/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// SteerTowardsTarget drive command allows robot to be driven in SteerTowardsTarget mode.
// This is the default command when robot in teleop mode

#include "commands/drive/TurnRightToHex.h"
#include "Robot.h"
#include "RobotMap.h"

TurnRightToHex::TurnRightToHex() {
  // Use AddRequirements here to declare subsystem dependencies
  AddRequirements (&Robot::m_MainDrive);
  AddRequirements(&Robot::m_NavX);
  AddRequirements(&Robot::m_Limelight);
}

// Called just before this Command runs the first time
void TurnRightToHex::Initialize() {

  // assume we have not seen target yet
  m_SawPrevious = false;

  // reset time spent in this command
  m_TotalTime = 0.0;

  // reset target in view time
  m_TargetinViewTime = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void TurnRightToHex::Execute() {
 
  // rotation speed
  float RotateSpeed = 0.15;

  // get limelight target data
  Limelight::HEXTARGET_DATA target = Robot::m_Limelight.GetTargetEstimation();
  
  static float IError = 0.0;

  // has camera detected target?
  if (target.Detected==true)
  {
      // indicate we have now seen target
      m_SawPrevious = true;

      // camera has detected target - run PI controller to determine rotate speed
      float angle = target.XAngle;
       
      if (fabs(angle) < 0.5)
        IError += angle * 0.00075;         // 0.0015
      else if (fabs(angle) < 1.5)
         IError += angle * 0.0006;       // 0.00125
      else if (fabs(angle) < 3.0)
        IError += angle * 0.0005;          // 0.001
      else if (fabs(angle) < 5.0)
        IError += angle * 0.00025;         // 0.0005
      else
        IError = 0.0;

      // determine desired rotational speed
      RotateSpeed = IError + 0.01*target.XAngle;
      
      // Limit rotational speed commanded by PI controller
      if (RotateSpeed > 0.15)
        RotateSpeed = 0.15;
      if (RotateSpeed < -0.15)
        RotateSpeed = -0.15;

      // if we are within 0.5deg of target, start counting up time
      if (fabs(angle)<0.5)
        m_onTargetTime += 0.02;
      else
        m_onTargetTime = 0.0;

     // target is within view, increment counter
     m_TargetinViewTime +=0.02;

  }
  else
  {
     // if we previously saw target, stop moving. Camera image may be intermittant
     if (m_SawPrevious)
       RotateSpeed = 0.0;

     // we do not have target lock
     m_onTargetTime = 0.0;

     // no target in view - reset timer
     m_TargetinViewTime =0.0;
  }
  
  // reset time spent in this command
  m_TotalTime += 0.02;

  // set motor speeds
  Robot::m_MainDrive.SetTankDrive (-RotateSpeed, RotateSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnRightToHex::IsFinished() {
  bool finished = false;

  // if we are on targetr for >0.1s, then we are finished
  if (m_onTargetTime > 0.1)
   finished = true;

  // if we have target in view, but for some reason not locking on, exit after 2s
  if (m_TargetinViewTime > 2.0)
    finished = true;
  
  // // if we spend more than 2.0s in this command, then exit - something is wrong as we are not seeing target
  // if (m_TotalTime > 3.0)
  //   finished = true;

  return finished;
}

// Called once after isFinished returns true
void TurnRightToHex::End(bool interrupted) {
  
  // set motor speeds
  Robot::m_MainDrive.SetTankDrive (0.0, 0.0);
}

