/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class IntakeOnOff : public frc2::CommandHelper<frc2::CommandBase, IntakeOnOff> {
  public:
  
  // Constructor - true to turn on, false to turn off
  // timeout - time to automatically turn off
  IntakeOnOff(bool On, float timeout=-1.0);
  
  // Called just before this Command runs the first time
  void Initialize() override;
  
  // Called repeatedly when this Command is scheduled to run
  void Execute() override;
  
  // Return true when this Command no longer needs to run execute()
  bool IsFinished() override;
  
  // Called once after isFinished returns true
  void End(bool interrupted) override;

  private:

  bool m_IntakeOn;
  float m_TimeOut;
  float m_OnTime;
    
};