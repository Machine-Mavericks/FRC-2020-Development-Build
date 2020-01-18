/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>

class FollowTargetTilStopped2 : public frc::Command {
 public:
  FollowTargetTilStopped2(float Speed, bool Pickup);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

  float m_Speed;

  bool m_SpeedLimit;

  float m_Timer1;
   // indicates if we have arrived at target
  bool m_AtTarget;

  // type of target we are pursuing
  //int m_TargetType;

  //Collision detection variables
  float m_LastAccelX;
  float m_LastAccelY;
  bool m_CollisionDetected;

  // PID variables
  float m_IntegratedError;
  float m_OldSpeed;

  float m_CurrentSpeed;

  bool m_Pickup;

  float m_AngleIntegratedError;
  float m_PreviousAngle;

  #define TARGET_COLLISION_THRESHOLD_DELTA_G 0.7
};