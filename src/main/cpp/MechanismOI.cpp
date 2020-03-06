/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "MechanismOI.h"
#include "RobotMap.h"
#include "commands/IntakeOnOff.h"
#include "commands/ShootBalls.h"
#include "commands/TiltDownUp.h"


// class constructor - executed upon creation of MechanismOI object
// creates joystick operator interfaces
MechanismOI::MechanismOI() {

    // create operator joystick objects
    MechanismJoystick = new Joystick(MECHANISM_CONTROLLER_PORT);

    // create robot operator button objects and associate with operator joystick and button #
    MechanismJoystickButtonBlue     = new JoystickButton(MechanismJoystick,3);
    MechanismJoystickButtonOrange   = new JoystickButton(MechanismJoystick,4);
    MechanismJoystickButtonRed      = new JoystickButton(MechanismJoystick,2);
    MechanismJoystickButtonGreen    = new JoystickButton(MechanismJoystick,1);
    MechanismJoystickButtonLeft     = new JoystickButton(MechanismJoystick,5);
    MechanismJoystickButtonRight    = new JoystickButton(MechanismJoystick,6);
    MechanismJoystickButtonLeftController  = new JoystickButton(MechanismJoystick,9);
    MechanismJoystickButtonRightController = new JoystickButton(MechanismJoystick,10);
    MechanismJoystickButtonBack      = new JoystickButton(MechanismJoystick,7);
    MechanismJoystickButtonStart     = new JoystickButton(MechanismJoystick,8);
    
    // intake on/off
    MechanismJoystickButtonStart->WhenPressed(new IntakeOnOff(true, 5.0));
    MechanismJoystickButtonBack->WhenPressed(new IntakeOnOff(false));

    // shoot balls
    MechanismJoystickButtonBlue->WhenPressed(new ShootBalls());

    // intake tilt
    MechanismJoystickButtonOrange->WhileHeld(new TiltDownUp(TiltDownUp::TiltUp));
    MechanismJoystickButtonRed->WhileHeld(new TiltDownUp(TiltDownUp::TiltMid));
    MechanismJoystickButtonGreen->WhileHeld(new TiltDownUp(TiltDownUp::TiltDown));

}
