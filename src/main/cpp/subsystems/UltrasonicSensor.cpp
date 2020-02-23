/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/AnalogInput.h>
#include "subsystems/UltrasonicSensor.h"
#include "RobotMap.h"
#include "Robot.h"

UltrasonicSensor::UltrasonicSensor(){
    m_UltrasonicSensor = new AnalogInput(ULTRASONIC_PORT);
}

// Returns distance to target
double UltrasonicSensor::GetRangeInches()
{ 
  // return motor drive current
    return m_UltrasonicSensor->GetVoltage();
}


// ------------- Shuffleboard Functions -------------

// update shuffle board with current target values
void UltrasonicSensor::InitializeShuffleBoard(void)
{
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("UltrasonicSensor");

    Range = Tab->Add("Range", 0.0).GetEntry();
 }

// update shuffle board with current target values
void UltrasonicSensor::UpdateShuffleBoard(void)
{
    Range.SetDouble(GetRangeInches());
    //Range.SetDouble(122.35);
}
