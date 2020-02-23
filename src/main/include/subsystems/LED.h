/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc2/command/SubsystemBase.h"
#include <frc/Shuffleboard/Shuffleboard.h>
#include <memory>

#include <hal/AddressableLEDTypes.h>
#include <hal/Types.h>
#include <units/units.h>
#include <wpi/ArrayRef.h>
#include <frc/AddressableLED.h>

#include "frc/ErrorBase.h"

using namespace frc;
//using namespace AddressableLED::LEDData;

class LED : public frc2::SubsystemBase {
 
 private:
  //frc::DigitalOutput m_DigitalIO;
    AddressableLED *m_AddressableLED;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  std::array<frc::AddressableLED::LEDData, 150> m_LEDBuffer;

 public:
    LED();

    void SetRGB(int r, int g, int b);

};

