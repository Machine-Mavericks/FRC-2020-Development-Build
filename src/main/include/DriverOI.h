/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/* DriverOI Class is the interface to the robot driver controls */

#pragma once

// include joystick API definitions for the DriverOI class to use
#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>

using namespace frc;
using namespace frc2;

class DriverOI {

    public:
    
    // class constructor - executed upon creation of DriverOI object
    DriverOI();

    // operator interface for robot driver operator interface
    // create pointers to individual joysticks robot drive
    Joystick *DriveJoystick;

    JoystickButton *DriveJoystickButtonBlue;
    JoystickButton *DriveJoystickButtonOrange;
    JoystickButton *DriveJoystickButtonRed;
    JoystickButton *DriveJoystickButtonGreen;
    JoystickButton *DriveJoystickButtonLeft;
    JoystickButton *DriveJoystickButtonRight;
    JoystickButton *DriveJoystickButtonLeftController;
    JoystickButton *DriveJoystickButtonRightController;
    JoystickButton *DriveJoystickButtonBack;
    JoystickButton *DriveJoystickButtonStart;
}; 