/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
//#include "RobotMap.h"
#include <frc/DigitalOutput.h>

using namespace frc;

class IndicatorLight : public frc::Subsystem {
 
 private:
  //frc::DigitalOutput m_DigitalIO;
  DigitalOutput *m_DigitalIO;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  IndicatorLight();

  void InitDefaultCommand() override;

  void ChangeLight(bool state);
};

