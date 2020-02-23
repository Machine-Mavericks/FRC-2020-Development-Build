/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Subsystem which handles the hardware portion of the Shooting for 2020. Designed around a Intake utilizing 2 Falcon motors,
// one top and one bottom.

#include "subsystems/Intake.h"
#include "wpi/StringMap.h"
#include "frc/shuffleboard/WidgetType.h"

// this is the constructor for the Intake subsystem.
Intake::Intake() {  

  // create individual motor control objects - assign unique CAN address to each motor drive
  m_Motor = new WPI_TalonFX(INTAKE_MOTOR_CANID);

  // configure motor drives with factory default settings
  m_Motor->ConfigFactoryDefault();

}

// ------------- Speed Control Functions -------------


// sets speed of intake drive - input 0 to 1.0 - percentage of output voltage 
void Intake::SetSpeed(float Speed){
    m_Motor->Set(ControlMode::PercentOutput,Speed);
}


void Intake::Stop(void) { 
    m_Motor->Set(ControlMode::PercentOutput,0);
}

// returns motor speeds (rpm)
// 10.0*(1/2048 counts per rev)*(60 s/min)
float Intake::GetSpeed(void) { return m_Motor->GetSelectedSensorVelocity(0) * 0.29296875;}

// return motor volts
float Intake::GetVolts(void) {  return m_Motor->GetBusVoltage(); }

// return motor current
float Intake::GetCurrent(void) { return m_Motor->GetSupplyCurrent();  }

// return motor temperature
float Intake::GetTemperature(void) { return m_Motor->GetTemperature(); }


// ------------- Shuffleboard Functions -------------

// initialize shuffleboard controls
void Intake::InitializeShuffleboard(void) {
      // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Intake");
    
    ShuffleboardLayout *l1 = &Tab->GetLayout("Speed (rpm)", BuiltInLayouts::kList);
    l1->WithPosition(0,0);
    l1->WithSize(1,1);
    Speed = l1->Add("Speed", 0.0).GetEntry();

    wpi::StringMap <std::shared_ptr<nt::Value>> SliderProperties {
      std::make_pair("min", nt::Value::MakeDouble(0.0)),
      std::make_pair("max", nt::Value::MakeDouble(1.0)) };
    Speed = Tab->Add("Speed", 0.0).WithWidget(BuiltInWidgets::kNumberSlider).WithPosition(1,0).WithSize(2,1).WithProperties(SliderProperties).GetEntry();

    ShuffleboardLayout *l2 = &Tab->GetLayout("Set Speed", BuiltInLayouts::kList);
    l2->WithPosition(1,2);
    l2->WithSize(1,2);
    Setting = l2->Add("Intake Motor", 0.0).GetEntry();

    ShuffleboardLayout *l3 = &Tab->GetLayout("Batt Voltage(v)", BuiltInLayouts::kList);
    l2->WithPosition(1,3);
    l2->WithSize(1,1);
    Volts = l3->Add("Voltage", 0.0).GetEntry();

    ShuffleboardLayout *l4 = &Tab->GetLayout("Current(A)", BuiltInLayouts::kList);
    l2->WithPosition(4,3);
    l2->WithSize(1,1);
    Current = l4->Add("Current", 0.0).GetEntry();

    ShuffleboardLayout *l6 = &Tab->GetLayout("Temperature(C)", BuiltInLayouts::kList);
    l6->WithPosition(4,4);
    l6->WithSize(1,1);
    Temperature = l6->Add("Temperature", 0.0).GetEntry();

}


// update shuffleboard - show speeds, and get commanded speed from slider
void Intake::UpdateShuffleboard(void){
    
    // write speed of top and bottom motors.
    Speed.SetDouble(GetSpeed());

    // get speed setting from slider value, and set motors accordingly
    float s = Speed.GetDouble(0.0);
    SetSpeed(s);

    // write voltage of top and bottom motors
    Setting.SetDouble(s);

    // write input voltages of motors
    Volts.SetDouble(GetVolts());

    // write motor currents
    Current.SetDouble(GetCurrent());

    // write motor temperature
    Temperature.SetDouble(GetTemperature());
}



