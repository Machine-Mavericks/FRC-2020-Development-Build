/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "commands/DriveWinch.h"
#include "Robot.h"
#include "RobotMap.h"

// Constructor
DriveWinch::DriveWinch() {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_Winch);
}

// Called just before this Command runs the first time
void DriveWinch::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveWinch::Execute() {
 
  // get robot current direction
  int position = Robot::m_Winch.GetEncoderPosition();// Robot::m_Winch.GetIntakeTiltTargetAnalog();

  position = position + 10000;
  if (position>POS_WINCHUP)
      position = POS_WINCHUP;
 
  
  // set position target of motor
  Robot::m_Winch.SetIntakeTiltTargetAnalog(position);

}

// Make this return true when this Command no longer needs to run execute()
bool DriveWinch::IsFinished() {
 // command ends when intake is at target
 int position = Robot::m_Winch.GetIntakeTiltTargetAnalog();
 return (position >=POS_WINCHUP); 
}

// Called once after isFinished returns true
void DriveWinch::End(bool interrupted) {
  
 // hold position
  Robot::m_Winch.SetIntakeTiltTargetAnalog(Robot::m_Winch.GetIntakeTiltTargetAnalog());
  // do nothing - leave intake in position control mode, at its current target setting
}