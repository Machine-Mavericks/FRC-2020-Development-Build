/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Agitator.h"
#include "wpi/StringMap.h"
#include "frc/shuffleboard/WidgetType.h"
#include "RobotMap.h"

// this is the constructor for the Intake subsystem.
Agitator::Agitator() {  

  // create individual motor control objects - assign unique CAN address to each motor drive
  m_AgitatorMotor = new WPI_TalonFX(AGITATOR_MOTOR_CANID);

  // configure motor drives with factory default settings
  m_AgitatorMotor->ConfigFactoryDefault();
}


// ------------- Speed Control Functions -------------


// sets speed of intake drive - input 0 to 1.0 - percentage of output voltage 
void Agitator::Start(){
    m_AgitatorMotor->Set(ControlMode::PercentOutput, 0.2);
}

void Agitator::Stop(void) { 
    m_AgitatorMotor->Set(ControlMode::PercentOutput,0);
}
