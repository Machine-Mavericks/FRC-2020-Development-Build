/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// SteerTowardsTarget drive command allows robot to be driven in SteerTowardsTarget mode.
// This is the default command when robot in teleop mode

#include "commands/UnJamIntake.h"
#include "Robot.h"
#include "RobotMap.h"

UnJamIntake::UnJamIntake() {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_Intake);

}

// Called just before this Command runs the first time
void UnJamIntake::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void UnJamIntake::Execute() {
  // get speed from joystick
  float speed = -Robot::m_MechanismOI.MechanismJoystick->GetRawAxis(RIGHT_JOYSTICK_Y_AXIS_ID);

  // limit
  if (speed>1.0) speed = 1.0;
  if (speed<0.0) speed = 0.0;

  Robot::m_Intake.SetSpeed(-speed);
}

// Make this return true when this Command no longer needs to run execute()
bool UnJamIntake::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void UnJamIntake::End(bool interrupted) {
  Robot::m_Intake.SetSpeed(0.0);
}