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

class SpinRotations : public frc2::CommandHelper<frc2::CommandBase, SpinRotations> {
 public:
 
  // Constructor - switches camera pipeline
  SpinRotations(int rotations);

  // Called just before this Command runs
  void Initialize() override;

  void Execute() override;

  bool IsFinished() override;

  void End(bool interrupted) override;

  private:

  int m_counter;
  int m_rotations;
  int m_currentColor;
  int m_initColor;
 
};
