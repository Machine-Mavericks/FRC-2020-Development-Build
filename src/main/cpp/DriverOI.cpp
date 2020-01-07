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

#include "commands/DriveTurnToAngle.h"  // TEMPORARY
#include "commands/DriveStraightDistance.h"
#include "commands/AutoRun.h"
#include "commands/LH2R.h"

// class constructor - executed upon creation of DriverOI object
// creates joystick operator interfaces
DriverOI::DriverOI() {
  
    // create drive joystick objects
    LeftJoystick = new Joystick(LEFT_JOYSTICK_PORT);
    RightJoystick = new Joystick(RIGHT_JOYSTICK_PORT);

    // Create left drive button objects and associate with left drive joystick and button #
    LeftJoystickButton1 = new JoystickButton(LeftJoystick,1);
    LeftJoystickButton2 = new JoystickButton(LeftJoystick,2);
    LeftJoystickButton3 = new JoystickButton(LeftJoystick,3);
    LeftJoystickButton4 = new JoystickButton(LeftJoystick,4);
    LeftJoystickButton5 = new JoystickButton(LeftJoystick,5);
    LeftJoystickButton6 = new JoystickButton(LeftJoystick,6);
    LeftJoystickButton7 = new JoystickButton(LeftJoystick,7);
    LeftJoystickButton8 = new JoystickButton(LeftJoystick,8);

    // Create left drive button objects and associate with left drive joystick and button #
    RightJoystickButton1 = new JoystickButton(RightJoystick,1);
    RightJoystickButton2 = new JoystickButton(RightJoystick,2);
    RightJoystickButton3 = new JoystickButton(RightJoystick,3);
    RightJoystickButton4 = new JoystickButton(RightJoystick,4);
    RightJoystickButton5 = new JoystickButton(RightJoystick,5);
    RightJoystickButton6 = new JoystickButton(RightJoystick,6);
    RightJoystickButton7 = new JoystickButton(RightJoystick,7);
    RightJoystickButton8 = new JoystickButton(RightJoystick,8);

    // -------------Button-Initiated Commands -------------
    
    // set robot arcade mode drive to function while right joystick trigger is pressed
    RightJoystickButton1->WhileHeld(new DriveArcade());


    // while left joystick trigger is held, automatically chase after target
    LeftJoystickButton1->WhileHeld(new DriveGoToTarget(0.35));


    // set limelight camera pipeline number - 0 for ball, 1 for chevron target
    // used to allow driver to select target type
    LeftJoystickButton3->WhenPressed(new CameraSwitchPipeline(0));
    LeftJoystickButton5->WhenPressed(new CameraSwitchPipeline(1));


    /*////////////////////// TEMPORARY /////////////////////////////
    // for testing only
    LeftJoystickButton4->WhileHeld(new AutoRun());

    LeftJoystickButton6->WhenPressed(new DriveTurnToAngle(90.0, 1.0, 0.5, 0.0));
    LeftJoystickButton8->WhenPressed(new DriveTurnToAngle(-90.0, 1.0, 0.5, 0.0));

    RightJoystickButton8->WhenPressed(new TiltHome());
    RightJoystickButton7->WhileHeld(new LH2R());
    */
}