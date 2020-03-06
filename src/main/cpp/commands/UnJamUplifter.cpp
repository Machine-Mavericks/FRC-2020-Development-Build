/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// SteerTowardsTarget drive command allows robot to be driven in SteerTowardsTarget mode.
// This is the default command when robot in teleop mode

#include "commands/UnJamUplifter.h"
#include "Robot.h"
#include "RobotMap.h"

UnJamUplifter::UnJamUplifter() {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_Uplifter);

}

// Called just before this Command runs the first time
void UnJamUplifter::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void UnJamUplifter::Execute() {
  // get speed from joystick
  float speed = -Robot::m_MechanismOI.MechanismJoystick->GetRawAxis(LEFT_JOYSTICK_Y_AXIS_ID);

  // limit
  if (speed>1.0) speed = 1.0;
  if (speed<0.15) speed = 0.15;

  Robot::m_Uplifter.SetSpeed(-speed);
}

// Make this return true when this Command no longer needs to run execute()
bool UnJamUplifter::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void UnJamUplifter::End(bool interrupted) {
  Robot::m_Uplifter.SetSpeed(0.0);
}