/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/AirCompressor.h"
#include "RobotMap.h"
#include <frc/Shuffleboard/Shuffleboard.h>

AirCompressor::AirCompressor() : Subsystem("Compressor") {

  // create compressor object
  m_Compressor = new Compressor();
}


void AirCompressor::InitDefaultCommand() {
  // no default command
}

// returns true of compressor is on
bool AirCompressor::IsCompressorActive() {
    return m_Compressor->Enabled();
}

// returns true if pressure switch is active
bool AirCompressor::IsPressureSwitchActive() {
    return m_Compressor->GetPressureSwitchValue();
}

// returns air compressor motor current (A)
float AirCompressor::GetMotorCurrent() {
  return m_Compressor->GetCompressorCurrent();
}


// ------------- Shuffleboard Functions -------------

void AirCompressor::InitializeShuffleBoard(void)
{
  // Main Tab
  ShuffleboardTab *Tab = &Shuffleboard::GetTab("Compressor");
    
  CompressorActive = Tab->Add("Compressor Active", false).GetEntry();
  PressureSW = Tab->Add("PSW Active", false).GetEntry();
  MotorCurrent = Tab->Add("Current", 0.0).GetEntry();
}

// update shuffle board with current values
void AirCompressor::UpdateShuffleBoard(void)
{
  CompressorActive.SetBoolean(IsCompressorActive());
  PressureSW.SetBoolean(IsPressureSwitchActive());
  MotorCurrent.SetDouble(GetMotorCurrent());
}