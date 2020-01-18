/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/InstantCommand.h>

#define BACKPISTON  0
#define FRONTPISTON 1
#define RETRACTED 0
#define EXTENDED  1

class Level2 : public frc::InstantCommand {
 public:
  
  //piston = 0 is rear, piston = 1 is front
  Level2(int piston, int pos);
  
  void Initialize() override;

  private:
  int m_piston;
  int m_pos;
  int positionfront;
  int positionrear;
};
