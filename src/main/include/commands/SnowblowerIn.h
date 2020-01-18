/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// This command is used to pull in ball into snowblower
// Motor is at reduced speed, and is current-limited to limit torque

#pragma once

#include <frc/commands/Command.h>

class SnowblowerIn : public frc::Command {
 public:

  // Constructs snowblower-in command
  SnowblowerIn();

  // Called just before this Command runs the first time
  void Initialize() override;

  // Called repeatedly when this Command is scheduled to run
  void Execute() override;

  // Make this return true when this Command no longer needs to run execute()
  bool IsFinished() override;

  // Called once after isFinished returns true
  void End() override;

  // Called when another command which requires one or more of the same subsystems is scheduled to run
  void Interrupted() override;

 private:

  // used to determine elapsed time(s)
  float timer;
};