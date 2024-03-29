/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#pragma once
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class TurnLeftToHex : public frc2::CommandHelper<frc2::CommandBase, TurnLeftToHex> {
  public:
  
  // Constructor
  TurnLeftToHex();
  
  // Called just before this Command runs the first time
  void Initialize() override;
  
  // Called repeatedly when this Command is scheduled to run
  void Execute() override;
  
  // Return true when this Command no longer needs to run execute()
  bool IsFinished() override;
  
  // Called once after isFinished returns true
  void End(bool interrupted) override;

  private:
  
  // indicates that we saw(detected) target
  bool m_SawPrevious;

  // length of time we are pointed to target
  float m_onTargetTime;

  // length of time target is view of camera
  float m_TargetinViewTime;

  // length of time we are in this command
  float m_TotalTime;
};
