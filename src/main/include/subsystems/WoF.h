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

#include <networkTables/networkTable.h>
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include <frc/util/color.h>

#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"

using namespace frc;

class WoF : public frc2::SubsystemBase {
 private:

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  // define motor 
  WPI_TalonFX *m_Motor;

  // encoder scaling factor
  const float RotationScaleFactor = ((kPi * WOF_WHEEL_DIAMETER) / 4096.0);

  
    // create pointer to ColorSensor object
    std::shared_ptr<NetworkTable> table;

    /* ColorSensor *m_ColorSensor; */

    frc::Color kBlueTarget;
    frc::Color kGreenTarget;
    frc::Color kRedTarget;
    frc::Color kYellowTarget;

    rev::ColorMatch m_colorMatcher;

  //construct color sensor object
  rev::ColorSensorV3 m_ColorSensor{frc::I2C::Port::kOnboard};


 public:

  // constructor - used to initialize specific hardware
  WoF();

    //get color reading
    int GetColor(void);

    void ResetEncoder(void);
};
