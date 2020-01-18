/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// This command is used to drive robot towards detected target

#pragma once

#include <frc/commands/Command.h>

class SteerTowardsTarget : public frc::Command {
  public:
  
  // Constructor
  DriveSteerTowardsTarget();
  
  // Called just before this Command runs the first time
  void Initialize() override;
  
  // Called repeatedly when this Command is scheduled to run
  void Execute() override;
  
  // Return true when this Command no longer needs to run execute()
  bool IsFinished() override;
  
  // Called once after isFinished returns true
  void End() override;
  
  // Called when another command which requires one or more of the same
  // subsystems is scheduled to run
  void Interrupted() override;

  private:
  
  // indicates if we have arrived at target
  bool m_AtTarget;

  // type of target we are pursuing
  int m_TargetType;
};

