/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// NavX Subsystem - Consists of Gyro, Compass, Accelerometer
// This subsystem provides access to all NavX functions

#pragma once

#include <frc/commands/Subsystem.h>
#include "AHRS.h"

using namespace frc;

class NavX : public frc::Subsystem {
  public:

  // constructor - used to initialize specific hardware
  NavX();

  // default command to run with the subsystem
  void InitDefaultCommand() override;

  // zero the yaw
  void ZeroYaw(void);

  // get current yaw
  float GetYaw(void);

  // get current roll rate
  float GetRoll(void);

  // get pitch
  float GetPitch(void);


  private:
  
  // create pointer to NavX object
  AHRS *ahrs;
};