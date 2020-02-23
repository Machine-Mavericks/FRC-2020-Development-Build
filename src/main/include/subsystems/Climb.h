/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include "frc/drive/DifferentialDrive.h"
#include "RobotMap.h"
#include <frc/Shuffleboard/Shuffleboard.h>
#include "frc/kinematics/DifferentialDriveWheelSpeeds.h"
#include <units/units.h>

using namespace frc;

class Climb : public frc2::SubsystemBase {
 private:

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  // define motor - assign to specific PWN channel
  WPI_TalonFX *m_Motor;

 public:

  // constructor - used to initialize specific hardware
  Climb();

  // Drive in Tank Drive - where left and right motors are driven independently
  void Lift();

  // reset the lift encoder to 0 value
  void ResetEncoder(void);

  // get lift encoder distance since last reset
  float GetEncoderDistance(void);

};
