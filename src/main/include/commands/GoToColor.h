/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// This command is used to change pipeline of camera

#pragma once

#include <frc2/command/CommandHelper.h>

class GoToColor : public frc2::CommandHelper<frc2::CommandBase, GoToColor> {
 public:
 
  // Constructor - switches camera pipeline
  GoToColor(int color);

  // Called just before this Command runs
  void Initialize() override;

  void Execute() override;

  bool IsFinished() override;

  void End(bool interrupted) override;

  private:

  int m_initColor;
 
};
