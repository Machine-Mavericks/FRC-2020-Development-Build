/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// RobotDrive subsystem represents the main robot drive system
// which consists of four drive motors - two for left, and two for right side

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc/Servo.h"
#include <frc/Shuffleboard/Shuffleboard.h>

using namespace frc;

class CameraTilt : public frc::Subsystem {
 
  public:

  // constructor - used to initialize specific hardware
  CameraTilt();

  // default command to run with the subsystem
  void InitDefaultCommand() override;

  // sets camera tilt 
  // == 0 for chevron
  // == 1 for ball
  void SetTiltPos(unsigned int Pos);

  // ------------- Shuffleboard Functions -------------

  void InitializeShuffleBoard(void);
  void UpdateShuffleBoard(void);

  private:

  // create pointer to servo motor
  Servo *m_Servo;
 
  nt::NetworkTableEntry BallAdjust, ChevronAdjust;
};