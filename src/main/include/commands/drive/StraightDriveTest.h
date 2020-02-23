/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Arcade drive command allows robot to be driven in arcade mode.
// This command is intended to be executed while right joystick trigger is pressed

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Shuffleboard/Shuffleboard.h>
#include <units/units.h>

class StraightDriveTest : public frc2::CommandHelper<frc2::CommandBase, StraightDriveTest> {
 public:
  
  // Constructor - Run once when command is created
  StraightDriveTest();

  // Called just before this Command runs the first time
  void Initialize() override;
  
  // Called repeatedly when this Command is scheduled to run
  void Execute() override;

  bool IsFinished() override;

  // Called once after isFinished returns true
  void End(bool interrupted) override;

};