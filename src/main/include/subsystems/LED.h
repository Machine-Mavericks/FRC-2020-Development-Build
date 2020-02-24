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

// length of LED strip
#define LEDLENGTH 150

class LED : public frc2::SubsystemBase {
 
private:
  
  // addressable LEDs
  AddressableLED *m_AddressableLED;
  
  // predefined LED colors
  std::array<frc::AddressableLED::LEDData, LEDLENGTH> m_BlueLEDs;
  std::array<frc::AddressableLED::LEDData, LEDLENGTH> m_OrangeLEDs;
  std::array<frc::AddressableLED::LEDData, LEDLENGTH> m_LEDsOff;

 public:
    // constructor
    LED();

    // preset colours
    void SetLEDsBlue(void);
    void SetLEDsOrange(void);
    void SetLEDsOff(void);
};

