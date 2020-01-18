/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/WPILib.h>
#include "DriverOI.h"
#include "RobotMap.h"
#include "Robot.h"
#include "commands/DriveArcade.h"
#include "commands/DriveGoToTarget.h"
#include "commands/CameraSwitchPipeline.h"
#include "commands/TiltHome.h"

#include "commands/DriveTurnToAngle.h" // TEMPORARY
#include "commands/DriveStraightDistance.h"
#include "commands/AutoRunLeft.h"
#include "commands/AutoRunRight.h"
#include "commands/LH2R.h"
#include "commands/DriveFollowPath.h"
#include "commands/HatchDropOffLow.h"
#include "commands/HatchDropOffMid.h"
#include "commands/HatchDropOffHigh.h"
#include "commands/HatchPickUp.h"
#include "commands/FollowTargetTilStopped.h"
#include "commands/Level2.h"
#include "commands/ClimbToLevelTwo.h"

// class constructor - executed upon creation of DriverOI object
// creates joystick operator interfaces
DriverOI::DriverOI()
{

    // create drive joystick objects
    LeftJoystick = new Joystick(LEFT_JOYSTICK_PORT);
    RightJoystick = new Joystick(RIGHT_JOYSTICK_PORT);

    // Create left drive button objects and associate with left drive joystick and button #
    LeftJoystickButton1 = new JoystickButton(LeftJoystick, 1);
    LeftJoystickButton2 = new JoystickButton(LeftJoystick, 2);
    LeftJoystickButton3 = new JoystickButton(LeftJoystick, 3);
    LeftJoystickButton4 = new JoystickButton(LeftJoystick, 4);
    LeftJoystickButton5 = new JoystickButton(LeftJoystick, 5);
    LeftJoystickButton6 = new JoystickButton(LeftJoystick, 6);
    LeftJoystickButton7 = new JoystickButton(LeftJoystick, 7);
    LeftJoystickButton8 = new JoystickButton(LeftJoystick, 8);
    LeftJoystickButton9 = new JoystickButton(LeftJoystick, 9);
    LeftJoystickButton10 = new JoystickButton(LeftJoystick, 10);
    LeftJoystickButton11 = new JoystickButton(LeftJoystick, 11);
    LeftJoystickButton12 = new JoystickButton(LeftJoystick, 12);

    // Create left drive button objects and associate with left drive joystick and button #
    RightJoystickButton1 = new JoystickButton(RightJoystick, 1);
    RightJoystickButton2 = new JoystickButton(RightJoystick, 2);
    RightJoystickButton3 = new JoystickButton(RightJoystick, 3);
    RightJoystickButton4 = new JoystickButton(RightJoystick, 4);
    RightJoystickButton5 = new JoystickButton(RightJoystick, 5);
    RightJoystickButton6 = new JoystickButton(RightJoystick, 6);
    RightJoystickButton7 = new JoystickButton(RightJoystick, 7);
    RightJoystickButton8 = new JoystickButton(RightJoystick, 8);
    RightJoystickButton9 = new JoystickButton(RightJoystick, 9);
    RightJoystickButton10 = new JoystickButton(RightJoystick, 10);
    RightJoystickButton11 = new JoystickButton(RightJoystick, 11);
    RightJoystickButton12 = new JoystickButton(RightJoystick, 12);

    // -------------Button-Initiated Commands -------------

    // set robot arcade mode drive to function while right joystick trigger is pressed
    RightJoystickButton1->WhileHeld(new DriveArcade());

    // while left joystick trigger is held, automatically chase after target
    LeftJoystickButton1->WhileHeld(new DriveSteerTowardsTarget());

    // set limelight camera pipeline number - 0 for ball, 1 for chevron target
    // used to allow driver to select target type
    LeftJoystickButton5->WhenPressed(new CameraSwitchPipeline(0));
    LeftJoystickButton3->WhenPressed(new CameraSwitchPipeline(1));

    LeftJoystickButton4->WhileHeld(new AutoRunLeft());

    // Hatch Drop Off Commands
    LeftJoystickButton7->WhileHeld(new HatchDropOffHigh());
    LeftJoystickButton9->WhileHeld(new HatchDropOffMid());
    LeftJoystickButton11->WhileHeld(new HatchDropOffLow());

    //RightJoystickButton7->WhenPressed(new DriveTurnToAngle(90.0, 1.0, 0.5, 0.0));
    //RightJoystickButton8->WhenPressed(new DriveTurnToAngle(-90.0, 1.0, 0.5, 0.0));

    //LeftJoystickButton4->WhileHeld(new AutoRun());
    //LeftJoystickButton4->WhenPressed(new FollowTargetTilStopped(0.3));

    //RightJoystickButton6->WhenPressed(new DriveFollowPath(true, "Cargo2Load"));
    //RightJoystickButton3->WhenPressed(new DriveFollowPath(false, "Cargo2Load"));

    // hatch drop-off (low) - note: duplicated with button #11 on left joystick
    RightJoystickButton4->WhileHeld(new HatchDropOffLow());

    // pickup hatch
    LeftJoystickButton6->WhileHeld(new HatchPickup());

    // Activate Pistons
    RightJoystickButton9->WhenPressed(new Level2(0, 1));
    RightJoystickButton10->WhenPressed(new Level2(0, 0));
    RightJoystickButton11->WhenPressed(new Level2(1, 1));
    RightJoystickButton12->WhenPressed(new Level2(1, 0));

    // Climb to level two
    RightJoystickButton8->WhileHeld(new ClimbToLevelTwo());

    /*////////////////////// TEMPORARY /////////////////////////////
    // for testing only
   

    LeftJoystickButton6->WhenPressed(new DriveTurnToAngle(90.0, 1.0, 0.5, 0.0));
    LeftJoystickButton8->WhenPressed(new DriveTurnToAngle(-90.0, 1.0, 0.5, 0.0));

    RightJoystickButton8->WhenPressed(new TiltHome());
    RightJoystickButton7->WhileHeld(new LH2R());
    */
}