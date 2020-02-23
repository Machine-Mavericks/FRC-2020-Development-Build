/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/MainDrive.h"


MainDrive::MainDrive() {  

  // create individual motor control objects - assign unique CAN address to each motor drive
  //m_MotorFrontLeft = new WPI_TalonFX(FRONT_LEFT_MOTOR_CANID);
  //m_MotorRearLeft = new WPI_TalonFX(REAR_LEFT_MOTOR_CANID);
  //m_MotorFrontRight = new WPI_TalonFX(FRONT_RIGHT_MOTOR_CANID);
  //m_MotorRearRight = new WPI_TalonFX(REAR_RIGHT_MOTOR_CANID);

 m_MotorFrontLeft = new WPI_TalonFX(FRONT_RIGHT_MOTOR_CANID);
  m_MotorRearLeft = new WPI_TalonFX(REAR_RIGHT_MOTOR_CANID);
  m_MotorFrontRight = new WPI_TalonFX(FRONT_LEFT_MOTOR_CANID);
  m_MotorRearRight = new WPI_TalonFX(REAR_LEFT_MOTOR_CANID);


  // configure motor drives with factory default settings
  m_MotorFrontLeft->ConfigFactoryDefault();
  m_MotorRearLeft->ConfigFactoryDefault();
  m_MotorFrontRight->ConfigFactoryDefault();
  m_MotorRearRight->ConfigFactoryDefault();

  // robot drives with intake facing forward
  //m_MotorFrontLeft->SetInverted(true);
  //m_MotorFrontRight->SetInverted(true);
  
  // set motors to run in voltage compensation mode
  SetVoltageCompensationLevel (MAXVOLTS);
  SetVoltageCompensationEnable (true);

  // set rear drives to follow front ones
  m_MotorRearLeft->Follow(*m_MotorFrontLeft);
  m_MotorRearRight->Follow(*m_MotorFrontRight);

  // create differential drive
  //m_Drive = new DifferentialDrive(*m_MotorFrontLeft, *m_MotorFrontRight);
  
  // reset encoders
  ResetLeftEncoder();
  ResetRightEncoder(); 
  }

// Drive in Tank Drive - where left and right motors are driven independently
// Inputs: LeftSpeed, RightSpeed - -1 <=speed <= +1.
// -1: full reverse
// 0: full stop
// +1: full forward
// Left motor is inverted
void MainDrive::SetTankDrive(float LeftSpeed, float RightSpeed)
{
  // make a local copy of left and right, so we can check each for range & invert left motor
  float left = LeftSpeed;
  float right = RightSpeed;

  // ensure speeds given to us are between -1.0 and 1.0
  if (left > 1.0)
    left = 1.0;
  if (left < -1.0)
    left = -1.0;

  if (right > 1.0)
    right = 1.0;
  if (right < -1.0)
    right = -1.0;

  // command drive to tankdrive at specified speeds
  SetTankDriveVolts(units::voltage::volt_t(m_VoltageCompensationLevel*left), units::voltage::volt_t(-m_VoltageCompensationLevel*right));
}

// Drive robot in Arcade Drive (Constant arc speed around z axis)
// Inputs: XSpeed, ZSpeed - -1 <=speed <= +1.
// -1: full reverse
// 0: full stop
// +1: full forward
void MainDrive::SetArcadeDrive(float XSpeed, float ZSpeed, bool Quickturn)
{
  // make a local copy of parameters so we can check each for range & invert left motor
  //float speed = XSpeed;
  //float rotation = -ZSpeed;

  // ensure speeds given to us are between -1.0 and 1.0
  //if (speed > 1.0)
  //  speed = 1.0;
  //if (speed < -1.0)
  //  speed = -1.0;
  //
  //if (rotation > 1.0)
  //  rotation = 1.0;
  //if (rotation < -1.0)
  //  rotation = -1.0;

  // drive motors at desired speed and rotation
  //m_Drive->ArcadeDrive(speed, rotation, Quickturn);
}


// ------------- Voltage Compentation -------------


// enable/disable motor voltage compenstation mode
void MainDrive::SetVoltageCompensationEnable (bool enable)
{
  m_MotorFrontLeft->EnableVoltageCompensation(enable);
  m_MotorRearLeft->EnableVoltageCompensation(enable);
  m_MotorFrontRight->EnableVoltageCompensation(enable);
  m_MotorRearRight->EnableVoltageCompensation(enable);
}

// set/get motor voltage compenstation level for linear performance
void MainDrive::SetVoltageCompensationLevel (float volts)
{
  m_VoltageCompensationLevel = volts;
  m_InvVoltageCompensationLevel = 1.0 / m_VoltageCompensationLevel;
  m_MotorFrontLeft->ConfigVoltageCompSaturation(volts, 0);
  m_MotorRearLeft->ConfigVoltageCompSaturation(volts, 0);
  m_MotorFrontRight->ConfigVoltageCompSaturation(volts, 0);
  m_MotorRearRight->ConfigVoltageCompSaturation(volts, 0);
}

// returns current motor voltage compenstation level
float MainDrive::GetVoltageCompenstationLevel (void)
{ return m_VoltageCompensationLevel; }


// ------------- Distance / Speed Functions -------------


// get left encoder distance since last reset
float MainDrive::GetLeftEncoderDistance(void)
{ return -m_MotorFrontLeft->GetSelectedSensorPosition(0) * EncoderScaleFactor; }

// get right encoder distance since last reset
float MainDrive::GetRightEncoderDistance(void)
{ return m_MotorFrontRight->GetSelectedSensorPosition(0) * EncoderScaleFactor; }

// get right/left encoder speed
// note: multiply by 10 as GetSelectedSensorVelocity returns pulses per 100ms
float MainDrive::GetLeftEncoderSpeed(void)
{ return -10.0*m_MotorFrontLeft->GetSelectedSensorVelocity(0) * EncoderScaleFactor; }

float MainDrive::GetRightEncoderSpeed(void)
{ return 10.0*m_MotorFrontRight->GetSelectedSensorVelocity(0) * EncoderScaleFactor; }


// ------------- Functions Required by Tractory Control -------------


// set motor volages for tank mode - inputs left/right volts
void MainDrive::SetTankDriveVolts(units::volt_t left, units::volt_t right)
{
  m_MotorFrontLeft->Set(ControlMode::PercentOutput, m_InvVoltageCompensationLevel * left.to<float>() );
  m_MotorFrontRight->Set(ControlMode::PercentOutput,m_InvVoltageCompensationLevel * right.to<float>() );
}


// return left/right drive speed (in m/s)
DifferentialDriveWheelSpeeds MainDrive::GetWheelSpeeds(void)
{
  return {units::meters_per_second_t(GetLeftEncoderSpeed()),
          units::meters_per_second_t(GetRightEncoderSpeed())};
}

// functions to return current motor voltage
float MainDrive::GetFrontLeftMotorVoltage(void)
{ return m_MotorFrontLeft->GetMotorOutputVoltage(); }
float MainDrive::GetRearLeftMotorVoltage(void)
{ return m_MotorRearLeft->GetMotorOutputVoltage(); }
float MainDrive::GetFrontRightMotorVoltage(void)
{ return m_MotorFrontRight->GetMotorOutputVoltage(); }
float MainDrive::GetRearRightMotorVoltage(void)
{ return m_MotorRearRight->GetMotorOutputVoltage(); }


// ------------- Drive Encoder Functions -------------

// reset the left encoder to 0 distance
void MainDrive::ResetLeftEncoder(void)
{
  // first parameter - encoder position, second parameter PID loop ID (use 0), third is timeout (use 0)
  m_MotorFrontLeft->SetSelectedSensorPosition(0, 0, 0);
}

// reset the right encoder to 0 value
void MainDrive::ResetRightEncoder(void)
{
   // first parameter - encoder position, second parameter PID loop ID (use 0), third is timeout (use 0)
  m_MotorFrontRight->SetSelectedSensorPosition(0, 0, 0);
}


// get left/right encoder raw values
int MainDrive::GetLeftEncoderTicks(void)
{ return m_MotorFrontLeft->GetSelectedSensorPosition(0); }

int MainDrive::GetRightEncoderTicks(void)
{ return -m_MotorFrontRight->GetSelectedSensorPosition(0); }


// ------------- Current Consumed by Drives -------------


// returns total current (A) consumed by drive subsystem
float MainDrive::GetTotalDriveCurrent(void)
{
  return m_MotorFrontLeft->GetSupplyCurrent() + m_MotorRearLeft->GetSupplyCurrent() +
        m_MotorFrontRight->GetSupplyCurrent() + m_MotorRearRight->GetSupplyCurrent();
}


// ------------- Temperatures -------------


// returns motor controller temperature (degC)
float MainDrive::GetFrontLeftTemp(void) { return m_MotorFrontLeft->GetTemperature(); }
float MainDrive::GetRearLeftTemp(void) { return m_MotorRearLeft->GetTemperature(); }
float MainDrive::GetFrontRightTemp(void) { return m_MotorFrontLeft->GetTemperature(); }
float MainDrive::GetRearRightTemp(void) { return m_MotorRearLeft->GetTemperature(); }


// ------------- Throttle Control -------------


// returns position of throttle control on shuffleboard - if not available, returns 1.0
float MainDrive::GetThrottle(void)
{ return Throttle.GetDouble(1.0); }


// ------------- Tank Control Mode -------------

// returns position of throttle control on shuffleboard - if not available, returns 1.0
bool MainDrive::GetTankMode(void)
{ return TankMode.GetBoolean(false); }


// ------------- Access to Motors -------------


// returns pointers to motors
WPI_TalonFX * MainDrive::GetFrontLeftMotor(void) { return m_MotorFrontLeft; }
WPI_TalonFX * MainDrive::GetRearLeftMotor(void) { return m_MotorRearLeft; }
WPI_TalonFX * MainDrive::GetFrontRightMotor(void) { return m_MotorFrontRight; }
WPI_TalonFX * MainDrive::GetRearRightMotor(void) { return m_MotorRearRight; }


// ------------- Shuffleboard Functions -------------

void MainDrive::InitializeShuffleBoard(void)
{
    // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("MainDrive");
    
    ShuffleboardLayout *l1 = &Tab->GetLayout("Distance (m)", BuiltInLayouts::kList);
    l1->WithPosition(0,0);
    l1->WithSize(1,2);
    LeftDistance = l1->Add("Left", 0.0).GetEntry();
    RightDistance = l1->Add("Right", 0.0).GetEntry();

    ShuffleboardLayout *l2 = &Tab->GetLayout("Speed (mps)", BuiltInLayouts::kList);
    l2->WithPosition(0,2);
    l2->WithSize(1,2);
    LeftSpeed = l2->Add("Left", 0.0).GetEntry();
    RightSpeed = l2->Add("Right", 0.0).GetEntry();

    ShuffleboardLayout *l3 = &Tab->GetLayout("Encoder Ticks", BuiltInLayouts::kList);
    l3->WithPosition(1,0);
    l3->WithSize(1,2);
    LeftEncoder = l3->Add("Left", 0.0).GetEntry();
    RightEncoder = l3->Add("Right", 0.0).GetEntry();

    ShuffleboardLayout *l4 = &Tab->GetLayout("Motor Volts(v)", BuiltInLayouts::kList);
    l4->WithPosition(2,0);
    l4->WithSize(1,4);
    LeftFrontVolts = l4->Add("FrontLeft", 0.0).GetEntry();
    LeftRearVolts = l4->Add("RearLeft", 0.0).GetEntry();
    RightFrontVolts = l4->Add("FrontRight", 0.0).GetEntry();
    RightRearVolts = l4->Add("RearRight", 0.0).GetEntry();

    ShuffleboardLayout *l5 = &Tab->GetLayout("Drive Current", BuiltInLayouts::kList);
    l5->WithPosition(1,2);
    l5->WithSize(1,1);
    TotalDriveCurrent = l5->Add("Total(A)", 0.0).GetEntry();

    ShuffleboardLayout *l6 = &Tab->GetLayout("Temperature (C)", BuiltInLayouts::kList);
    l6->WithPosition(3,0);
    l6->WithSize(1,4);
    LeftFrontTemp = l6->Add("FrontLeft", 0.0).GetEntry();
    LeftRearTemp = l6->Add("RearLeft", 0.0).GetEntry();
    RightFrontTemp = l6->Add("FrontRight", 0.0).GetEntry();
    RightRearTemp = l6->Add("RearRight", 0.0).GetEntry();

    wpi::StringMap <std::shared_ptr<nt::Value>> SliderProperties {
      std::make_pair("min", nt::Value::MakeDouble(0.0)),
      std::make_pair("max", nt::Value::MakeDouble(1.0)) };
    Throttle = Tab->AddPersistent("Throttle", 0.0).WithWidget(BuiltInWidgets::kNumberSlider).WithPosition(4,0).WithSize(2,1).WithProperties(SliderProperties).GetEntry();

    TankMode = Tab->AddPersistent("TankModeSwitch", false). WithWidget(BuiltInWidgets::kToggleSwitch).WithPosition(4,2).WithSize(1,1).GetEntry();
}

// update shuffle board with current drive values
void MainDrive::UpdateShuffleBoard(void)
{
  // write drive distance for left and right side
  LeftDistance.SetDouble(GetLeftEncoderDistance());
  RightDistance.SetDouble(GetRightEncoderDistance());
 
  // write drive speed for left and right side
  LeftSpeed.SetDouble(GetLeftEncoderSpeed());
  RightSpeed.SetDouble(GetRightEncoderSpeed());
  
  // write encoder values for left and right side
  LeftEncoder.SetDouble(GetLeftEncoderTicks());
  RightEncoder.SetDouble(GetRightEncoderTicks());

  // write total drive current
  TotalDriveCurrent.SetDouble(GetTotalDriveCurrent());

  // temperatures
  LeftFrontTemp.SetDouble(GetFrontLeftTemp());
  LeftRearTemp.SetDouble(GetRearLeftTemp());
  RightFrontTemp.SetDouble(GetFrontRightTemp());
  RightRearTemp.SetDouble(GetRearRightTemp());

  // motor voltages
  LeftFrontVolts.SetDouble(GetFrontLeftMotorVoltage());
  LeftRearVolts.SetDouble(GetRearLeftMotorVoltage());
  RightFrontVolts.SetDouble(GetFrontRightMotorVoltage());
  RightRearVolts.SetDouble(GetRearRightMotorVoltage());
}

