/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>

class AutoRunLeft : public frc::CommandGroup {
 public:
  AutoRunLeft();

  // Called once after isFinished returns true
  void End() override;
  
  // Called when another command which requires one or more of the same
  // subsystems is scheduled to run
  void Interrupted() override;
};
