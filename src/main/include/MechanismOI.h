/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/* MechanismOI Class is the interface to the robot mechanism controls */

#pragma once

// include joystick API definitions for the MechanismOI class to use
#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>

using namespace frc;
using namespace frc2;

class MechanismOI {

    public:
    
    // class constructor - executed upon creation of MechanismOI object
    MechanismOI();

    // operator interface for robot accessories operator interface
     Joystick *MechanismJoystick;
   
    // individual buttons for  robot operator joystick
    JoystickButton *MechanismJoystickButton1;
    JoystickButton *MechanismJoystickButton2;
    JoystickButton *MechanismJoystickButton3;
    JoystickButton *MechanismJoystickButton4;
    JoystickButton *MechanismJoystickButton5;
    JoystickButton *MechanismJoystickButton6;
    JoystickButton *MechanismJoystickButton7;
    JoystickButton *MechanismJoystickButton8;

}; 