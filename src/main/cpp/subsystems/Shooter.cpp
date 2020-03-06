/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Subsystem which handles the hardware portion of the Shooting for 2020. Designed around a Shooter utilizing 2 Falcon motors,
// one top and one bottom.

#include "subsystems/Shooter.h"
#include "wpi/StringMap.h"
#include "frc/shuffleboard/WidgetType.h"

// this is the constructor for the Shooter subsystem.
Shooter::Shooter() {  

  // create individual motor control objects - assign unique CAN address to each motor drive
  m_MotorTop = new WPI_TalonFX(SHOOTER_1_MOTOR_CANID);
  m_MotorBottom = new WPI_TalonFX(SHOOTER_2_MOTOR_CANID);

  // configure motor drives with factory default settings
  m_MotorTop->ConfigFactoryDefault();
  m_MotorBottom->ConfigFactoryDefault();
 
  m_MotorBottom->Follow(*m_MotorTop);
  m_MotorBottom->SetInverted(true);

  // set up motor speed controller 
  //m_MotorTop->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
  m_MotorTop->Config_kF(0, 0.00, 0);
  m_MotorTop->Config_kP(0, 0.32, 0);
  m_MotorTop->Config_kI(0, 0.00008, 0);
  // set peak forward voltage to 100%, peak reverse voltage to 0.0
  m_MotorTop->ConfigPeakOutputForward(1, 0);
  m_MotorTop->ConfigPeakOutputReverse(0.0, 0);

  m_MotorTop->ConfigMaxIntegralAccumulator(0, 8000000.0, 0);

  // Set maximum allowed posotion controller closed loop error 
  //m_MotorTop->ConfigAllowableClosedloopError(0, 35.0, 0);


  // limit motor to max ramp rate of 0.2s from 0 to 100% throttle
  m_MotorTop->ConfigClosedloopRamp(0.2, 0);
}


// ------------- Speed Control Functions -------------

// set shooter speed - input RPM
void Shooter::SetSpeed(float Speed){
    // convert rpm to #encoder pulses per 100ms
    m_MotorTop->Set(ControlMode::Velocity,Speed * 3.41333333);
}

// returns motor speeds (rpm)
// 10.0*(1/2048 counts per rev)*(1/60 s/min)
float Shooter::GetTopSpeed(void) { return m_MotorTop->GetSelectedSensorVelocity(0) * 0.29296875;}
float Shooter::GetBottomSpeed(void) { return m_MotorBottom->GetSelectedSensorVelocity(0) * 0.29296875;}

// return motor volts
float Shooter::GetTopVolts(void) {  return m_MotorTop->GetBusVoltage(); }
float Shooter::GetBottomVolts(void) {  return m_MotorBottom->GetBusVoltage(); }

// return motor current
float Shooter::GetTopCurrent(void) { return m_MotorTop->GetSupplyCurrent();  }
float Shooter::GetBottomCurrent(void) { return m_MotorBottom->GetSupplyCurrent();}

// returns speed selector slider (from shuffleboard) value
float Shooter::GetSpeedSliderValue (void) { return SpeedSlider.GetDouble(0.0); }

// returns speed selector slider (from shuffleboard) value
float Shooter::GetIdleSpeedSliderValue (void) { return IdleSpeedSlider.GetDouble(0.5); }


// ------------- Shuffleboard Functions -------------

// initialize shuffleboard controls
void Shooter::InitializeShuffleboard(void) {
      // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Shooter");
    
    ShuffleboardLayout *l1 = &Tab->GetLayout("Speed (rpm)", BuiltInLayouts::kList);
    l1->WithPosition(0,0);
    l1->WithSize(1,2);
    TopSpeed = l1->Add("Top", 0.0).GetEntry();
    BottomSpeed = l1->Add("Bottom", 0.0).GetEntry();

    wpi::StringMap <std::shared_ptr<nt::Value>> SpeedSliderProperties {
      std::make_pair("min", nt::Value::MakeDouble(0.0)),
      std::make_pair("max", nt::Value::MakeDouble(6300.0)) };
    SpeedSlider = Tab->Add("Speed", 0.0).WithWidget(BuiltInWidgets::kNumberSlider).WithPosition(1,0).WithSize(2,1).WithProperties(SpeedSliderProperties).GetEntry();

    ShuffleboardLayout *l2 = &Tab->GetLayout("Set Speed", BuiltInLayouts::kList);
    l2->WithPosition(3,0);
    l2->WithSize(1,2);
    TopSetting = l2->Add("Top", 0.0).GetEntry();
    BottomSetting = l2->Add("Bottom", 0.0).GetEntry();

    ShuffleboardLayout *l3 = &Tab->GetLayout("Batt Voltage(v)", BuiltInLayouts::kList);
    l3->WithPosition(4,0);
    l3->WithSize(1,2);
    TopVolts = l3->Add("Top", 0.0).GetEntry();
    BottomVolts = l3->Add("Bottom", 0.0).GetEntry();

    ShuffleboardLayout *l4 = &Tab->GetLayout("Current(A)", BuiltInLayouts::kList);
    l4->WithPosition(5,0);
    l4->WithSize(1,2);
    TopCurrent = l4->Add("Top", 0.0).GetEntry();
    BottomCurrent = l4->Add("Bottom", 0.0).GetEntry();

    wpi::StringMap <std::shared_ptr<nt::Value>> IdleSliderProperties {
      std::make_pair("min", nt::Value::MakeDouble(0.0)),
      std::make_pair("max", nt::Value::MakeDouble(6300.0)) };
    IdleSpeedSlider = Tab->Add("Idle Speed", 3000.0).WithWidget(BuiltInWidgets::kNumberSlider).WithPosition(1,2).WithSize(2,1).WithProperties(IdleSliderProperties).GetEntry();
}


// update shuffleboard - show speeds, and get commanded speed from slider
void Shooter::UpdateShuffleboard(void) {
    
    // write speed of top and bottom motors.
    TopSpeed.SetDouble(GetTopSpeed());
    BottomSpeed.SetDouble(GetBottomSpeed());

    // get speed setting from slider value, and set motors accordingly
    float s = SpeedSlider.GetDouble(0.0);
    //SetSpeed(s);
    // write voltage of top and bottom motors
    TopSetting.SetDouble(s);
    BottomSetting.SetDouble(s);

    // write input voltages of motors
    TopVolts.SetDouble(GetTopVolts());
    BottomVolts.SetDouble(GetBottomVolts());

    // write motor currents
    TopCurrent.SetDouble(GetTopCurrent());
    BottomCurrent.SetDouble(GetBottomCurrent());
}