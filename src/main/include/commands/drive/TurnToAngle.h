/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class TurnToAngle : public frc2::CommandHelper<frc2::CommandBase, TurnToAngle> {
 public:

  // constructor - Turn robot by fixed angle, with speed limit
  TurnToAngle(float Angle, float Tolerance, float zSpeed, float xSpeed);
  
  // Called just before this Command runs the first time
  void Initialize() override;
  
  // Called repeatedly when this Command is scheduled to run
  void Execute() override;

  // Make this return true when this Command no longer needs to run execute()
  bool IsFinished() override;

  // Called once after isFinished returns true
  void End(bool interrupted) override;


  private:
  
  // angle to turn robot
  float m_Angle;
  float m_Tolerance;
  
  // speed limits to turn robot at
  float m_zSpeed;
  float m_xSpeed;

  // integrated error
  float m_IntegratedError;

  // previous sample
  float m_PreviousYaw;

  // timer for when at target
  float m_Timer;

};