/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// This command is used to change pipeline of camera

#pragma once

#include <frc/commands/InstantCommand.h>

class CameraSwitchPipeline : public frc::InstantCommand {
 public:
 
  // Constructor - switches camera pipeline
  CameraSwitchPipeline(unsigned int Pipeline);

  // Called just before this Command runs
  void Initialize() override;

  private:

  // pipeline to change camera to
  unsigned int m_Pipeline;
};
