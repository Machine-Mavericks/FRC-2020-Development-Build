/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriverOI.h"
#include "RobotMap.h"

// commands to run when joystick buttons pressed
#include "commands/drive/Arcade.h"
#include "commands/drive/SteerTowardsTarget.h"
#include "commands/drive/StraightDriveTest.h"
#include "commands/drive/FollowPath.h"
#include "commands/drive/TurnRightToHex.h"
#include "commands/drive/TurnLeftToHex.h"
#include "commands/ShootBalls.h"
#include "TrajectoryConstants.h"


// class constructor - executed upon creation of DriverOI object
// creates joystick operator interfaces
DriverOI::DriverOI() {
  
    // create drive joystick objects
    DriveJoystick = new Joystick(DRIVE_JOYSTICK_PORT);

    // Create left drive button objects and associate with left drive joystick and button #
    DriveJoystickButtonBlue     = new JoystickButton(DriveJoystick,3);
    DriveJoystickButtonOrange   = new JoystickButton(DriveJoystick,4);
    DriveJoystickButtonRed      = new JoystickButton(DriveJoystick,2);
    DriveJoystickButtonGreen    = new JoystickButton(DriveJoystick,1);
    DriveJoystickButtonLeft     = new JoystickButton(DriveJoystick,5);
    DriveJoystickButtonRight    = new JoystickButton(DriveJoystick,6);
    DriveJoystickButtonLeftController  = new JoystickButton(DriveJoystick,9);
    DriveJoystickButtonRightController = new JoystickButton(DriveJoystick,10);
    DriveJoystickButtonBack      = new JoystickButton(DriveJoystick,7);
    DriveJoystickButtonStart     = new JoystickButton(DriveJoystick,8);


    // -------------Button-Initiated Commands -------------
    
    // set robot arcade mode drive to function while right joystick trigger is pressed
    DriveJoystickButtonRight->WhileHeld(new Arcade());
    
    // turn left/right to hex target
    DriveJoystickButtonBack->WhileHeld(new TurnLeftToHex());
    DriveJoystickButtonStart->WhileHeld(new TurnRightToHex());

    //LeftJoystickButton1->WhileHeld(new SteerTowardsTarget());
    //LeftJoystickButton1->WhileHeld(new StraightDriveTest());
    //DriveJoystickButtonBlue->WhileHeld(new FollowPath(CTrajectoryConstants::olivia, false));

    DriveJoystickButtonBlue->WhenPressed(new ShootBalls());
    
    // while left joystick trigger is held, automatically chase after target
    //LeftJoystickButton1->WhileHeld(new GoToTarget(0.35));

    //when joystick is pressed, follow path
    //RightJoystickButton6->WhenPressed(new DriveFollowPath(false, "Cargo2FarRocket")); */
} 