/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Compressor.h>
#include <frc/Shuffleboard/Shuffleboard.h>

using namespace frc;

class AirCompressor : public frc::Subsystem {
 public:
  AirCompressor();
  void InitDefaultCommand() override;

  // returns true of compressor is on
  bool IsCompressorActive();
  
  // returns true if pressure switch is active
  bool IsPressureSwitchActive();

  // returns air compressor motor current (A)
  float GetMotorCurrent();

  // update shuffle board with current values
  void InitializeShuffleBoard(void);
  void UpdateShuffleBoard(void);

  private: 
  // air compressor
  Compressor *m_Compressor;

  // Shubbleboard Controls
  nt::NetworkTableEntry CompressorActive, PressureSW, MotorCurrent; 
};