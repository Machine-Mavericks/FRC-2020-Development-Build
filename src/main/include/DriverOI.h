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
    // create pointers to individual joysticks for left/right robot drive to support tank mode driving
    Joystick *LeftJoystick;
    Joystick *RightJoystick;

    // create pointers for individual buttons for left joystick
    JoystickButton *LeftJoystickButton1;
    JoystickButton *LeftJoystickButton2;
    JoystickButton *LeftJoystickButton3;
    JoystickButton *LeftJoystickButton4;
    JoystickButton *LeftJoystickButton5;
    JoystickButton *LeftJoystickButton6;
    JoystickButton *LeftJoystickButton7;
    JoystickButton *LeftJoystickButton8;

    // create pointers for individual buttons for right joystick
    JoystickButton *RightJoystickButton1;
    JoystickButton *RightJoystickButton2;
    JoystickButton *RightJoystickButton3;
    JoystickButton *RightJoystickButton4;
    JoystickButton *RightJoystickButton5;
    JoystickButton *RightJoystickButton6;
    JoystickButton *RightJoystickButton7;
    JoystickButton *RightJoystickButton8; 
}; 