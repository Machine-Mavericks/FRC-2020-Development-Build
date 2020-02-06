/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Limight subsytem contains all functions needed to access camera

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <networkTables/networkTable.h>
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include <frc/util/color.h>

#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"

using namespace frc;

class ColorSensor : public frc2::SubsystemBase {
    public:
  
    // constructor - used to initialize specific hardware
    ColorSensor();
  
    // ---------- Camera Data Functions
    // default command to run with the subsystem
    int GetColor(void);

    private:

    // create pointer to ColorSensor object
    std::shared_ptr<NetworkTable> table;

    /* ColorSensor *m_ColorSensor; */

    frc::Color kBlueTarget;
    frc::Color kGreenTarget;
    frc::Color kRedTarget;
    frc::Color kYellowTarget;

    rev::ColorMatch m_colorMatcher;

  /**
   * A Rev Color Sensor V3 object is constructed with an I2C port as a 
   * parameter. The device will be automatically initialized with default 
   * parameters.
   */
  rev::ColorSensorV3 m_ColorSensor{frc::I2C::Port::kOnboard};
};


