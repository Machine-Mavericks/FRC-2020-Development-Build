/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/AnalogInput.h>
#include <frc/Shuffleboard/Shuffleboard.h>

using namespace frc;

class UltrasonicSensor : public frc2::SubsystemBase {
 
 private:
  //frc::DigitalOutput m_DigitalIO;
    AnalogInput *m_UltrasonicSensor;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  // Shuffleboard Controls
  nt::NetworkTableEntry Range;

 public:
    UltrasonicSensor();

    double GetRangeInches();

    void InitializeShuffleBoard(void);

    void UpdateShuffleBoard(void);
};

