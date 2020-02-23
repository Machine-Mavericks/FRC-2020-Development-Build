/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Arcade drive command allows robot to be driven in arcade mode.
// This command is intended to be executed while right joystick trigger is pressed

#include "commands/Drive/StraightDriveTest.h"
#include "Robot.h"
#include <math.h>
#include "RobotMap.h"

StraightDriveTest::StraightDriveTest() {
  // Use AddRequirements here to declare subsystem dependencies
  AddRequirements (&Robot::m_MainDrive);

  
}

// Called just before this Command runs the first time
void StraightDriveTest::Initialize() {
  Robot::m_MainDrive.SetTankDriveVolts(units::voltage::volt_t(-2.0), units::voltage::volt_t(2.0));
}

// Called repeatedly when this Command is scheduled to run
void StraightDriveTest::Execute() {
  //Robot::m_MainDrive.SetTankDrive(0.5, 0.5);
  // Robot::m_MainDrive.SetTankDriveVolts(units::voltage::volt_t(-3.0), units::voltage::volt_t(3.0));
}

bool StraightDriveTest::IsFinished()
{ return false;
}
// Called once after isFinished returns true
void StraightDriveTest::End(bool interrupted) {
  Robot::m_MainDrive.SetTankDriveVolts(units::voltage::volt_t(-0.0), units::voltage::volt_t(0.0));
//Robot::m_MainDrive.SetTankDrive(0.0, 0.0);
}



