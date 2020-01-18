/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Tank drive command allows robot to be driven in tank mode.
// This is the default command when robot in teleop mode

#include "commands/DriveTank.h"
#include "Robot.h"
#include <math.h>
#include "RobotMap.h"

DriveTank::DriveTank() {
  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_MainDrive);

  // tank drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void DriveTank::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveTank::Execute() {
  // create variables for left and right joystick y axes
  float raw_left_y, raw_right_y, left_y, right_y, throttle;

  // get joystick y values from joystick
  raw_left_y = Robot::m_DriverOI.LeftJoystick->GetRawAxis(JOYSTICK_Y_AXIS_ID );
  raw_right_y = Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_Y_AXIS_ID );

  // get joystick right throttle to control maximum robot speed
  // adjust throttle to give value between 0 and +1.0
  // use negative of throttle so that +1 represents throttle forward position
  throttle = 0.5 * (1.0 + -Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_THROTTLE_AXIS_ID));

  // implement non-linear joystick response curves
  right_y = LINEAR_WEIGHT * raw_right_y + CUBIC_WEIGHT * pow(raw_right_y, 3); 
  left_y = LINEAR_WEIGHT * raw_left_y + CUBIC_WEIGHT * pow(raw_left_y, 3); 

  // apply throttle control (scaling factor) to both left and right values.
  right_y = right_y * throttle;
  left_y = left_y * throttle;

  // set main drive tank speeds
  Robot::m_MainDrive.SetTankDrive (left_y, right_y);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveTank::IsFinished() {
  // since this is default mode, always return false - command never ends
  return false;
}

// Called once after isFinished returns true
void DriveTank::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveTank::Interrupted() {}
