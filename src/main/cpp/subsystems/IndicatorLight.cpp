/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IndicatorLight.h"
#include "RobotMap.h"

IndicatorLight::IndicatorLight() : Subsystem("IndicatorLight") {
      m_DigitalIO = new DigitalOutput(LIGHT_CHANNEL);
}

void IndicatorLight::InitDefaultCommand(){}

void IndicatorLight::ChangeLight(bool state) {
    m_DigitalIO->Set(state);
}
