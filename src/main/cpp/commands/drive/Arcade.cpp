/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Arcade drive command allows robot to be driven in arcade mode.
// This command is intended to be executed while right joystick trigger is pressed

#include "commands/Drive/Arcade.h"
#include <math.h>


Arcade::Arcade() {
  // Use AddRequirements here to declare subsystem dependencies
  AddRequirements (&Robot::m_MainDrive);
}

// Called just before this Command runs the first time
void Arcade::Initialize() {

  m_Drive = new DifferentialDrive(*Robot::m_MainDrive.GetFrontLeftMotor(),
                                   *Robot::m_MainDrive.GetFrontRightMotor());
}

// Called repeatedly when this Command is scheduled to run
void Arcade::Execute() {
  // create variables joystick x and y
  float raw_y, raw_x, y, x, throttle;

  // get joystick y values from joystick
  // raw_y = Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_Y_AXIS_ID);
  // raw_x = Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_X_AXIS_ID);

  // get raw x and y values from joystick, -ve corrects for backwards direction
   raw_y = -Robot::m_DriverOI.DriveJoystick->GetRawAxis(RIGHT_JOYSTICK_Y_AXIS_ID);
   raw_x = -Robot::m_DriverOI.DriveJoystick->GetRawAxis(RIGHT_JOYSTICK_X_AXIS_ID );

  // create variable for throttle - get from shuffleboard
  throttle = Robot::m_MainDrive.GetThrottle();

  // implement non-linear joystick response curves
  y = LINEAR_WEIGHT * raw_y + CUBIC_WEIGHT * pow(raw_y, 3); 
  x = LINEAR_WEIGHT * raw_x + CUBIC_WEIGHT * pow(raw_x, 3); 

  // apply throttle control (scaling factor) to both left and right values.
  y = y * throttle;
  x = x * throttle; 

  // set main drive tank speeds
  if (m_Drive!=NULL)
    m_Drive->ArcadeDrive(-y, x, false);
}

// Called once after isFinished returns true
void Arcade::End(bool interrupted) {
  // finished using differential drive - delete object
  if (m_Drive !=NULL)
    delete m_Drive;
}


