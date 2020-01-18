/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>

class DriveStraightTilStopped : public frc::Command {
 public:

  // constructor - Turn robot by fixed Distance, with speed limit
  DriveStraightTilStopped(float Distance, float Speed);
  
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
  
  // Distance to drive robot
  float m_Distance;
  
  // speed limit to turn robot at
  float m_Speed;

  // integrated error
  float m_IntegratedError;

  // reference angle
  float m_ReferenceAngle;

  float m_Timer;
 
  float m_Timer1;

  bool m_CollisionDetected;

  double m_LastAccelX;

  double m_LastAccelY;

  #define COLLISION_THRESHOLD_DELTA_G 0.2
};