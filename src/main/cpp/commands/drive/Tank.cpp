/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Tank drive command allows robot to be driven in tank mode.
// This is the default command when robot in teleop mode

#include "commands/drive/Tank.h"
#include "Robot.h"
#include <math.h>
#include "RobotMap.h"

Tank::Tank() {
  // Use AddRequirements here to declare subsystem dependencies
  AddRequirements(&Robot::m_MainDrive);
  
  // tank drive command is interruptable
  //SetInterruptible(true);
}

// Called just before this Command runs the first time
void Tank::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Tank::Execute() {
  // create variables for left and right joystick y axes
  float raw_x, raw_y, left_wheels, right_wheels;
  
  // get joystick y values from joystick
  // raw_y = Robot::m_DriverOI.LeftJoystick->GetRawAxis(JOYSTICK_Y_AXIS_ID );
  // raw_x = Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_X_AXIS_ID );

  if (Robot::m_MainDrive.GetTankMode() == true)
  {
    // get values from joystick (assumes logitech controller)
    left_wheels = Robot::m_DriverOI.DriveJoystick->GetRawAxis(LEFT_JOYSTICK_Y_AXIS_ID);
    right_wheels = Robot::m_DriverOI.DriveJoystick->GetRawAxis(RIGHT_JOYSTICK_Y_AXIS_ID); 
  }   
  else
  { 
    // get values from joystick (assumes logitech controller)
    raw_y = Robot::m_DriverOI.DriveJoystick->GetRawAxis(LEFT_JOYSTICK_Y_AXIS_ID);
    raw_x = Robot::m_DriverOI.DriveJoystick->GetRawAxis(RIGHT_JOYSTICK_X_AXIS_ID);
    // calculate wheel speeds from forward and rotation values
    left_wheels = (raw_y - 0.5*raw_x)/1.5;
    right_wheels = (raw_y + 0.5*raw_x)/1.5;
  }

  // create variable for throttle - get from shuffleboard
  float throttle = Robot::m_MainDrive.GetThrottle();

  // apply throttle control
  left_wheels = left_wheels * throttle;
  right_wheels = right_wheels* throttle;

  // set motor speeds
  Robot::m_MainDrive.SetTankDrive (left_wheels, right_wheels);
}

// Make this return true when this Command no longer needs to run execute()
bool Tank::IsFinished() {
  // since this is default mode, always return false - command never ends
  return false;
}

// Called once after isFinished returns true
void Tank::End(bool interrupted) {}

