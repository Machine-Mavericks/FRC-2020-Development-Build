/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/WPILib.h>
#include "MechanismOI.h"
#include "RobotMap.h"
#include "commands/ElevatorUpDownPosition.h"
#include "commands/ClawOpen.h"
#include "commands/ClawGrabHatch.h"
#include "commands/ClawGrabBall.h"
#include "commands/TiltUp.h"
#include "commands/TiltDown.h"
#include "commands/TiltMid.h"
#include "commands/SnowblowerIn.h"
#include "commands/SnowblowerOut.h"
#include "commands/SnowblowerOff.h"
#include "commands/HatchPickup.h"

// class constructor - executed upon creation of MechanismOI object
// creates joystick operator interfaces
MechanismOI::MechanismOI() {

    // create operator joystick objects
    MechanismJoystick = new Joystick(MECHANISM_CONTROLLER_PORT);

    // create robot operator button objects and associate with operator joystick and button #
    MechanismJoystickButton1 = new JoystickButton(MechanismJoystick,1);
    MechanismJoystickButton2 = new JoystickButton(MechanismJoystick,2);
    MechanismJoystickButton3 = new JoystickButton(MechanismJoystick,3);
    MechanismJoystickButton4 = new JoystickButton(MechanismJoystick,4);
    MechanismJoystickButton5 = new JoystickButton(MechanismJoystick,5);
    MechanismJoystickButton6 = new JoystickButton(MechanismJoystick,6);
    MechanismJoystickButton7 = new JoystickButton(MechanismJoystick,7);
    MechanismJoystickButton8 = new JoystickButton(MechanismJoystick,8);

    // move elevator up or down one position
    MechanismJoystickButton1->WhenPressed(new ElevatorUpDownPosition(false));
    MechanismJoystickButton4->WhenPressed(new ElevatorUpDownPosition(true));
    
    #ifdef ROBOTTYPE_CLAW
        // open and close claw
        MechanismJoystickButton3->WhenPressed(new ClawGrabBall());
        MechanismJoystickButton2->WhenPressed(new ClawOpen());
        MechanismJoystickButton6->WhenPressed(new ClawGrabHatch());
    #endif
    #ifdef ROBOTTYPE_SNOWBLOWER
        MechanismJoystickButton3->WhenPressed(new SnowblowerIn());
        MechanismJoystickButton2->WhenPressed(new SnowblowerOut());
        MechanismJoystickButton6->WhenPressed(new SnowblowerOff());
    #endif

    // tilt claw
    MechanismJoystickButton5->WhenPressed(new TiltMid());
    MechanismJoystickButton7->WhenPressed(new TiltDown());
    MechanismJoystickButton8->WhenPressed(new TiltUp());

 

    // open/close LobClaw
    //MechanismJoystickButton3->WhenPressed(new LobClawOpenClose(1));
    //MechanismJoystickButton2->WhenPressed(new LobClawOpenClose(0));
 

}
  