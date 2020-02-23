/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// This command is used to change pipeline of camera

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class ChangeLED : public frc2::CommandHelper<frc2::CommandBase, ChangeLED> {
 public:
 
  // Constructor - switches camera pipeline
  ChangeLED();

  // Called just before this Command runs
  void Initialize() override;

  void Execute() override;

  bool IsFinished() override;

  void End(bool interrupted) override;

  private:

  int counter;
  bool LEDON;
};
