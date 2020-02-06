/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// NavX Subsystem - Consists of Gyro, Compass, Accelerometer
// This subsystem provides access to all NavX functions

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Shuffleboard/Shuffleboard.h>
#include "AHRS.h"

using namespace frc;

class NavX : public frc2::SubsystemBase {
  public:

  // constructor - used to initialize specific hardware
  NavX();

  // zero the yaw
  void ZeroYaw(void);

  // get current yaw
  float GetYaw(void);

  // get current roll rate
  float GetRoll(void);

  // get pitch
  float GetPitch(void);

  // get X acceleration
  float GetAccelX(void);
 
  // get Y acceleration
  float GetAccelY(void);


  // ------------- Shuffleboard Functions -------------

  void InitializeShuffleBoard(void);
  void UpdateShuffleBoard(void);

  private:
  
  // create pointer to NavX object
  AHRS *ahrs;

  // Shubbleboard Controls
  nt::NetworkTableEntry Yaw, Pitch, Roll; 
  nt::NetworkTableEntry AccelX, AccelY;
};