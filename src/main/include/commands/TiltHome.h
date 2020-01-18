/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// THe TiltHome module homes the tilt subsystem by gently moving the
// tilt to upright position at reduced speed (and torque), at which point 
// then puts motor drive into position control mode.

#pragma once

#include <frc/commands/Command.h>

class TiltHome : public frc::Command {
  public:
  // Constructor for TiltHome command
  TiltHome();
  
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
  // indicates true of command has sucessfully finished
  bool m_Finished;

  // time duration for which we have been attempted to home tilt
  float m_Time;
};
