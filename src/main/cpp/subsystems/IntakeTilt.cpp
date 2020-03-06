/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IntakeTilt.h"
#include "wpi/StringMap.h"
#include "frc/shuffleboard/WidgetType.h"

// this is the constructor for the Intake subsystem.
IntakeTilt::IntakeTilt() {  

 // create individual motor control objects- assign unique CAN adress to motor drive-
  m_Motor = new WPI_TalonFX(WRIST_MOTOR_CANID);

  // set factory default settings
  m_Motor->ConfigFactoryDefault();

  // reverse motor direction
  m_Motor->SetInverted(false);

  // sets direction of the encoder - set to true to invert phase (to change encoder direction)
  //m_Motor->SetSensorPhase(false);

  // set up forward direction soft (software) limit - set to maximum allowed encoder pulse counts at IntakeTilt top. Disable until subsystem has been rehomed
  m_Motor->ConfigForwardSoftLimitEnable(true,0);
  m_Motor->ConfigForwardSoftLimitThreshold(TILT_SOFT_LIMIT_MAX);

  // set up reverse direction soft limit - assumes encoder pulse at bottom is 0. Disable until subsystem has been rehomed
  m_Motor->ConfigReverseSoftLimitEnable(true, 0);
  m_Motor->ConfigReverseSoftLimitThreshold(TILT_SOFT_LIMIT_MIN); 

  // set motor ramp rate (from neutral to full) used to avoid sudden changes in spee
  // First parameter slotID - motor drive can support 4 different sets of PID valued
  m_Motor-> ConfigClosedloopRamp(INTAKETILT_DRIVE_MAXRAMP, 0);

  // Set position feedback control error gainss - we only need slot 0
  // Second parameter is PGain/IGain/DGain as applicable
  // Third parameter is timeout value - set to 0 for no checking
  // Note: Full-scale error output is 1023. I believe inputs to PID loop are encoder pulse counts.
  m_Motor->Config_kP(0, TILT_PGAIN, 0);
  m_Motor->Config_kI(0, TILT_IGAIN, 0);
  m_Motor->Config_kD(0, TILT_DGAIN, 0);

  // set integration maximum accumulator value
  m_Motor->ConfigMaxIntegralAccumulator(0, TILT_MAX_INTEGRAL_ACCUMULATOR, 0);
 
  // Set maximum allowed posotion controller closed loop error 
  m_Motor->ConfigAllowableClosedloopError(0, TILT_ALLOWABLE_CLOSEDLOOP_ERROR, 0);

  //reset encoder
  ResetEncoderPosition();
}





// ------------- Encoder-Related Functions -------------


// Resets IntakeTilt encoder position value
// USE ONLY WHEN IntakeTilt AT HOME POSITION (BOTTOM?)
void IntakeTilt::ResetEncoderPosition(void){
  // first parameter - encoder position,
  m_Motor->SetSelectedSensorPosition(0);
}

// Returns IntakeTilt encoder position value (in raw sensor units)
int IntakeTilt::GetEncoderPosition(void){  
  // return position of primary feedback sensor for PID loop ID (use 0)
  return m_Motor->GetSelectedSensorPosition(0);
}

// Function to command IntakeTilt to move to a fixed position
// Input: Target position (in sensor units)
void IntakeTilt::SetIntakeTiltTargetAnalog(int pos){

  // ensure position in valid range of drive
  if (pos<TILT_SOFT_LIMIT_MIN )
      pos=TILT_SOFT_LIMIT_MIN;
  if (pos>TILT_SOFT_LIMIT_MAX)
      pos=TILT_SOFT_LIMIT_MAX;

  // set motor target position
  m_Motor->Set(ControlMode::Position, pos);
}

// Function to get current IntakeTilt target position
// Output: Target position (in sensor units)
int IntakeTilt::GetIntakeTiltTargetAnalog(void){
  return m_Motor->GetClosedLoopTarget(0);
}



// ------------- Motor-Related Functions -------------


// return motor volts
float IntakeTilt::GetVolts(void) {  return m_Motor->GetBusVoltage(); }

// return motor current
float IntakeTilt::GetCurrent(void) { return m_Motor->GetSupplyCurrent();  }

// return motor temperature
float IntakeTilt::GetTemperature(void) { return m_Motor->GetTemperature(); }



// ------------- Shuffleboard Functions -------------

// initialize shuffleboard controls
void IntakeTilt::InitializeShuffleboard(void) {
      // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("IntakeTilt");
    
    MotorEncoder=Tab->Add("Encoder", 0.0).WithPosition(0,0).GetEntry();
    MotorTarget=Tab->Add("Target", 0.0).WithPosition(1,0).GetEntry();
    
    ShuffleboardLayout *l1 = &Tab->GetLayout("Positions", BuiltInLayouts::kList);
    l1->WithPosition(3,0);
    l1->WithSize(1,2);
    l1->Add("Up", TILT_UP_POSITION);
    l1->Add("Mid", TILT_MID_POSITION);
    l1->Add("Down", TILT_DOWN_POSITION);
    
    ShuffleboardLayout *l2 = &Tab->GetLayout("Adjusts", BuiltInLayouts::kList);
    l2->WithPosition(4,0);
    l2->WithSize(1,2);
    PosUpAdjust=l2->AddPersistent("Up", 0.0).GetEntry();
    PosMidAdjust=l2->AddPersistent("Mid", 0.0).GetEntry();
    PosDownAdjust=l2->AddPersistent("Down", 0.0).GetEntry();

    ShuffleboardLayout *l3 = &Tab->GetLayout("Batt Voltage(v)", BuiltInLayouts::kList);
    l3->WithPosition(4,0);
    l3->WithSize(1,2);
    Volts = l3->Add("Voltage", 0.0).GetEntry();

    ShuffleboardLayout *l4 = &Tab->GetLayout("Current(A)", BuiltInLayouts::kList);
    l4->WithPosition(5,0);
    l4->WithSize(1,2);
    Current = l4->Add("Current", 0.0).GetEntry();

    ShuffleboardLayout *l5 = &Tab->GetLayout("Temperature(C)", BuiltInLayouts::kList);
    l5->WithPosition(6,0);
    l5->WithSize(1,2);
    Temperature = l5->Add("Temperature", 0.0).GetEntry();

}


// update shuffleboard
void IntakeTilt::UpdateShuffleboard(void) {
    
  // write encoder position and position controller target (# encoder pulses)
  MotorEncoder.SetDouble(GetEncoderPosition());
  MotorTarget.SetDouble(GetIntakeTiltTargetAnalog());

  // write input voltages of motors
  Volts.SetDouble(GetVolts());

  // write motor currents
  Current.SetDouble(GetCurrent());

  // write motor temperature
  Temperature.SetDouble(GetTemperature());
}