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

using namespace frc;

class CameraTilt : public frc::Subsystem {
  private:

  // create pointer to servo motor
  Servo *m_Servo;
 
  public:

  // constructor - used to initialize specific hardware
  CameraTilt();

  // default command to run with the subsystem
  void InitDefaultCommand() override;

  // sets camera tilt 
  void SetTilt(float value);
};