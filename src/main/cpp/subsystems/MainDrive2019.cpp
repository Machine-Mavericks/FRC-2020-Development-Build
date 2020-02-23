/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/MainDrive2019.h"

MainDrive2019::MainDrive2019(){

  // create individual motor control objects - assign unique CAN address to each motor drive
  m_MotorFrontLeft = new WPI_VictorSPX(FRONT_LEFT_MOTOR_CANID);
  m_MotorRearLeft = new WPI_VictorSPX(REAR_LEFT_MOTOR_CANID);
  m_MotorFrontRight = new WPI_VictorSPX(FRONT_RIGHT_MOTOR_CANID);
  m_MotorRearRight = new WPI_VictorSPX(REAR_RIGHT_MOTOR_CANID);

  // configure motor drives with factory default settings
  m_MotorFrontLeft->ConfigFactoryDefault();
  m_MotorRearLeft->ConfigFactoryDefault();
  m_MotorFrontRight->ConfigFactoryDefault();
  m_MotorRearRight->ConfigFactoryDefault();

   // set motors to run in voltage compensation mode
  SetVoltageCompensationLevel (MAXVOLTS);
  SetVoltageCompensationEnable (true);
  
  // set rear drives to follow front ones
  m_MotorRearLeft->Follow(*m_MotorFrontLeft);
  m_MotorRearRight->Follow(*m_MotorFrontRight);

  // create differential drive
  //m_Drive = new DifferentialDrive(*m_MotorFrontLeft, *m_MotorFrontRight);

  // create encoder objects - reverse left encoder so it reads +ve in forward direction
  m_EncoderRight = new Encoder(RIGHT_ENCODER_CHANNELA_ID, RIGHT_ENCODER_CHANNELB_ID);
  m_EncoderLeft = new Encoder(LEFT_ENCODER_CHANNELA_ID, LEFT_ENCODER_CHANNELB_ID, true);

  // Use SetDistancePerPulse to set the multiplier for GetDistance
  m_EncoderRight->SetDistancePerPulse(EncoderScaleFactor);
  m_EncoderLeft->SetDistancePerPulse(EncoderScaleFactor);

  // reset encoders
  ResetLeftEncoder();
  ResetRightEncoder();
  
  //enable safety feature
  m_MotorFrontLeft->SetExpiration(15.0);
  //m_MotorRearLeft->SetExpiration(15.0);
  m_MotorFrontRight->SetExpiration(15.0);
  //m_MotorRearRight->SetExpiration(15.0);

  m_MotorFrontLeft->SetSafetyEnabled(true);
  m_MotorRearLeft->SetSafetyEnabled(false);
  m_MotorFrontRight->SetSafetyEnabled(true);
  m_MotorRearRight->SetSafetyEnabled(false);

}

// Drive in Tank Drive - where left and right motors are driven independently
// Inputs: LeftSpeed, RightSpeed - -1 <=speed <= +1.
// -1: full reverse
// 0: full stop
// +1: full forward
// Left motor is inverted
void MainDrive2019::SetTankDrive(float LeftSpeed, float RightSpeed)
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
  SetTankDriveVolts(units::voltage::volt_t(m_VoltageCompenstationLevel*left), units::voltage::volt_t(-m_VoltageCompenstationLevel*right));
}

// Drive robot in Arcade Drive (Constant arc speed around z axis)
// Inputs: XSpeed, ZSpeed - -1 <=speed <= +1.
// -1: full reverse
// 0: full stop
// +1: full forward
void MainDrive2019::SetArcadeDrive(float XSpeed, float ZSpeed, bool Quickturn)
{

  // make a local copy of parameters so we can check each for range & invert left motor
  // float speed = -XSpeed;
  // float rotation = ZSpeed;

  // ensure speeds given to us are between -1.0 and 1.0
  // if (speed > 1.0)
  //   speed = 1.0;
  // if (speed < -1.0)
  //   speed = -1.0;

  // if (rotation > 1.0)
  //   rotation = 1.0;
  // if (rotation < -1.0)
  //   rotation = -1.0;

  // drive motors at desired speed and rotation
  //m_Drive->ArcadeDrive(speed, rotation, Quickturn);
}


// ------------- Voltage Compentation -------------


// enable/disable motor voltage compenstation mode
void MainDrive2019::SetVoltageCompensationEnable (bool enable)
{
  m_MotorFrontLeft->EnableVoltageCompensation(enable);
  m_MotorRearLeft->EnableVoltageCompensation(enable);
  m_MotorFrontRight->EnableVoltageCompensation(enable);
  m_MotorRearRight->EnableVoltageCompensation(enable);
}

// set/get motor voltage compenstation level for linear performance
void MainDrive2019::SetVoltageCompensationLevel (float volts)
{
  m_VoltageCompenstationLevel = volts;
  m_MotorFrontLeft->ConfigVoltageCompSaturation(volts, 0);
  m_MotorRearLeft->ConfigVoltageCompSaturation(volts, 0);
  m_MotorFrontRight->ConfigVoltageCompSaturation(volts, 0);
  m_MotorRearRight->ConfigVoltageCompSaturation(volts, 0);
}

// returns current motor voltage compenstation level
float MainDrive2019::GetVoltageCompenstationLevel (void)
{ return m_VoltageCompenstationLevel; }


// ------------- Distance / Speed Functions -------------


// get left encoder distance since last reset
float MainDrive2019::GetLeftEncoderDistance(void)
{ return m_EncoderLeft->GetDistance(); }

// get right encoder distance since last reset
float MainDrive2019::GetRightEncoderDistance(void)
{ return m_EncoderRight->GetDistance(); }

// get left encoder distance since last reset
float MainDrive2019::GetLeftEncoderSpeed(void)
{ return m_EncoderLeft->GetRate(); }

// get left encoder distance since last reset
float MainDrive2019::GetRightEncoderSpeed(void)
{ return m_EncoderRight->GetRate(); }


// ------------- Functions Required by Tractory Control -------------


// set motor volages for tank mode - inputs left/right volts
void MainDrive2019::SetTankDriveVolts(units::volt_t left, units::volt_t right)
{
 m_MotorFrontLeft->Set(ControlMode::PercentOutput, -0.083333 * left.to<float>() );
   m_MotorFrontRight->Set(ControlMode::PercentOutput, -0.083333 * right.to<float>() );
}


// return left/right drive speed (in m/s)
DifferentialDriveWheelSpeeds MainDrive2019::GetWheelSpeeds(void)
{
  // function included for future compatability
  return {units::meters_per_second_t(GetLeftEncoderSpeed()),  
          units::meters_per_second_t(GetRightEncoderSpeed())};
}

// functions to return current motor voltage
float MainDrive2019::GetFrontLeftMotorVoltage(void)
{ return m_MotorFrontLeft->GetMotorOutputVoltage(); }
float MainDrive2019::GetRearLeftMotorVoltage(void)
{ return m_MotorRearLeft->GetMotorOutputVoltage(); }
float MainDrive2019::GetFrontRightMotorVoltage(void)
{ return m_MotorFrontRight->GetMotorOutputVoltage(); }
float MainDrive2019::GetRearRightMotorVoltage(void)
{ return m_MotorRearRight->GetMotorOutputVoltage(); }


// ------------- Drive Encoder Functions -------------

// reset the left encoder to 0 distance
void MainDrive2019::ResetLeftEncoder(void)
{ m_EncoderLeft->Reset(); }

// reset the right encoder to 0 value
void MainDrive2019::ResetRightEncoder(void)
{ m_EncoderRight->Reset(); }


// get left/right encoder raw values
int MainDrive2019::GetLeftEncoderTicks(void)
{ return m_EncoderLeft->GetRaw(); }

int MainDrive2019::GetRightEncoderTicks(void)
{ return m_EncoderRight->GetRaw(); }


// ------------- Throttle Control -------------


// returns position of throttle control on shuffleboard - if not available, returns 1.0
float MainDrive2019::GetThrottle(void)
{ return Throttle.GetDouble(1.0); }


// ------------- Tank Control Mode -------------

// returns position of throttle control on shuffleboard - if not available, returns 1.0
bool MainDrive2019::GetTankMode(void)
{ return TankMode.GetBoolean(false); }


// ------------- Access to Motors -------------


// returns pointers to motors
WPI_VictorSPX * MainDrive2019::GetFrontLeftMotor(void) { return m_MotorFrontLeft; }
WPI_VictorSPX * MainDrive2019::GetRearLeftMotor(void) { return m_MotorRearLeft; }
WPI_VictorSPX * MainDrive2019::GetFrontRightMotor(void) { return m_MotorFrontRight; }
WPI_VictorSPX * MainDrive2019::GetRearRightMotor(void) { return m_MotorRearRight; }



// ------------- Shuffleboard Functions -------------

void MainDrive2019::InitializeShuffleBoard(void)
{
    // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Drive2019");
    
    ShuffleboardLayout *l1 = &Tab->GetLayout("Distance(m)", BuiltInLayouts::kList);
    l1->WithPosition(8,0);
    l1->WithSize(1,2);
    LeftDistance = l1->Add("Left", 0.0).GetEntry();
    RightDistance = l1->Add("Right", 0.0).GetEntry();

    ShuffleboardLayout *l2 = &Tab->GetLayout("Speed (mps)", BuiltInLayouts::kList);
    l2->WithPosition(1,0);
    l2->WithSize(1,2);
    LeftSpeed = l2->Add("Left", 0.0).GetEntry();
    RightSpeed = l2->Add("Right", 0.0).GetEntry();

    ShuffleboardLayout *l3 = &Tab->GetLayout("Encoder TIcks", BuiltInLayouts::kList);
    l3->WithPosition(2,0);
    l3->WithSize(1,2);
    LeftEncoder = l3->Add("Left", 0.0).GetEntry();
    RightEncoder = l3->Add("Right", 0.0).GetEntry();

    ShuffleboardLayout *l4 = &Tab->GetLayout("Motor Volts(v)", BuiltInLayouts::kList);
    l4->WithPosition(3,0);
    l4->WithSize(1,3);
    LeftFrontVolts = l4->Add("FrontLeft", 0.0).GetEntry();
    LeftRearVolts = l4->Add("RearLeft", 0.0).GetEntry();
    RightFrontVolts = l4->Add("FrontRight", 0.0).GetEntry();
    RightRearVolts = l4->Add("RearRight", 0.0).GetEntry();

    wpi::StringMap <std::shared_ptr<nt::Value>> SliderProperties {
      std::make_pair("min", nt::Value::MakeDouble(0.0)),
      std::make_pair("max", nt::Value::MakeDouble(1.0)) };
    Throttle = Tab->AddPersistent("Throttle", 0.0).WithWidget(BuiltInWidgets::kNumberSlider).WithPosition(4,0).WithSize(2,1).WithProperties(SliderProperties).GetEntry();

    TankMode = Tab->AddPersistent("TankModeSwitch", false). WithWidget(BuiltInWidgets::kToggleSwitch).WithPosition(4,2).WithSize(1,1).GetEntry();
}

// update shuffle board with current drive values
void MainDrive2019::UpdateShuffleBoard(void)
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
 
  // motor voltages
  LeftFrontVolts.SetDouble(GetFrontLeftMotorVoltage());
  LeftRearVolts.SetDouble(GetRearLeftMotorVoltage());
  RightFrontVolts.SetDouble(GetFrontRightMotorVoltage());
  RightRearVolts.SetDouble(GetRearRightMotorVoltage());

}
