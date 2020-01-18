/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Snowblower.h"
#include "RobotMap.h"

Snowblower::Snowblower() : Subsystem("Snowblower") {

  // create individual motor control objects- assign unique CAN adress to motor drive- defined in RobotMap.h
  m_Motor = new WPI_TalonSRX(SNOWBLOWER_MOTOR_CANID);

  // configure motor drive with factory default settings
  m_Motor->ConfigFactoryDefault();

  m_Motor->SetSafetyEnabled(false);

}

void Snowblower::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}


// ------------- Snowblower Functions -------------


// Set motor speed 
// Input: speed between -1.0 and 1.0
void Snowblower::SetMotorSpeed(float speed){
  m_Motor->Set(ControlMode::PercentOutput, speed);
}

// Set max motor current (A)
void Snowblower::SetMaxMotorCurrent(float current) {
  m_Motor->ConfigContinuousCurrentLimit(current);
  m_Motor->EnableCurrentLimit(true);
}

// Returns motor drive current (amps)
float Snowblower::GetMotorCurrent(void)
{ 
  // return motor drive current
  return m_Motor->GetOutputCurrent();
}



// ------------- Shuffleboard Functions -------------

void Snowblower::InitializeShuffleBoard(void)
{
    // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Snowblower");

    MotorCurrent = Tab->Add("Current", 0.0).GetEntry();
    //MotorVoltage = Tab->Add("Voltage", 0.0).GetEntry();
}

// update shuffle board with current drive values
void Snowblower::UpdateShuffleBoard(void) {

  MotorCurrent.SetDouble(GetMotorCurrent());
}



