/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Arcade drive command allows robot to be driven in arcade mode.
// This command is intended to be executed while right joystick trigger is pressed

#include "commands/DriveArcade.h"
#include "Robot.h"
#include <math.h>
#include "RobotMap.h"

DriveArcade::DriveArcade() {
  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_MainDrive);

  // arcade drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void DriveArcade::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveArcade::Execute() {
  // create variables joystick x and y
  float raw_y, raw_x, y, x, throttle;

  // get joystick y values from joystick
  raw_y = Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_Y_AXIS_ID);
  raw_x = Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_X_AXIS_ID);

  // get joystick right throttle to control maximum robot speed
  // adjust throttle to give value between 0 and +1.0
  // use negative of throttle so that +1 represents throttle forward position
  throttle = 0.5 * (1.0 + -Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_THROTTLE_AXIS_ID));

  // implement non-linear joystick response curves
  y = LINEAR_WEIGHT * raw_y + CUBIC_WEIGHT * pow(raw_y, 3); 
  x = LINEAR_WEIGHT * raw_x + CUBIC_WEIGHT * pow(raw_x, 3); 

  // apply throttle control (scaling factor) to both left and right values.
  y = y * throttle;
  x = x * throttle;

  // set main drive tank speeds
  Robot::m_MainDrive.SetArcadeDrive (y, x, false);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveArcade::IsFinished() {
  // since this is default mode, always return false - command never ends
  return false;
}

// Called once after isFinished returns true
void DriveArcade::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveArcade::Interrupted() {
}
