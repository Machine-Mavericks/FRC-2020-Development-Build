/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>

class StraightDistance : public frc::Command {
 public:

  // constructor - Turn robot by fixed distance, with speed limit
  StraightDistance(float Distance, float Speed);
  
  // Called just before this Command runs the first time
  void Initialize() override;
  
  // Called repeatedly when this Command is scheduled to run
  void Execute() override;

  // Make this return true when this Command no longer needs to run execute()
  bool IsFinished() override;

  // Called once after isFinished returns true
  void End() override;
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>

class StraightDistance : public frc::Command {
 public:

  // constructor - Turn robot by fixed distance, with speed limit
  StraightDistance(float Distance, float Tolerance, float Speed);
  
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
  
  // distance to drive robot
  float m_Distance;
  
  // stopping tolerance
  float m_Tolerance;

  // speed limit to turn robot at
  float m_Speed;

  // integrated error
  float m_IntegratedError;

  // reference angle
  float m_ReferenceAngle;

  // previous distance error - used for differential error
  float m_PrevError;

  float m_Timer;

};
  // Called when another command which requires one or more of the same subsystems is scheduled to run
  void Interrupted() override;

  private:
  
  // distance to drive robot
  float m_Distance;
  
  // speed limit to turn robot at
  float m_Speed;

  // integrated error
  float m_IntegratedError;
};