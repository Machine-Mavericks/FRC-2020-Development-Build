/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/MainDrive.h"
#include "RobotMap.h"
#include "commands/DriveTank.h"

MainDrive::MainDrive() : Subsystem("MainDrive")
{

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

  // set rear drives to follow front ones
  m_MotorRearLeft->Follow(*m_MotorFrontLeft);
  m_MotorRearRight->Follow(*m_MotorFrontRight);

  // create differential drive
  m_Drive = new DifferentialDrive(*m_MotorFrontLeft, *m_MotorFrontRight);

  // create encoder objects - reverse left encoder so it reads +ve in forward direction
  m_EncoderRight = new Encoder(RIGHT_ENCODER_CHANNELA_ID, RIGHT_ENCODER_CHANNELB_ID);
  m_EncoderLeft = new Encoder(LEFT_ENCODER_CHANNELA_ID, LEFT_ENCODER_CHANNELB_ID, true);

  // Use SetDistancePerPulse to set the multiplier for GetDistance
  m_EncoderRight->SetDistancePerPulse((kPi * WHEEL_DIAMETER) / (float)ENCODER_PULSE_PER_REVOLUTION);
  m_EncoderLeft->SetDistancePerPulse((kPi * WHEEL_DIAMETER) / (float)ENCODER_PULSE_PER_REVOLUTION);

  // reset encoders
  ResetLeftEncoder();
  ResetRightEncoder();
  
  //disable safety feature
  m_MotorFrontLeft->SetSafetyEnabled(false);
  m_MotorRearLeft->SetSafetyEnabled(false);
  m_MotorFrontRight->SetSafetyEnabled(false);
  m_MotorRearRight->SetSafetyEnabled(false);
}

// default command to run with the subsystem
void MainDrive::InitDefaultCommand()
{
  // Set default command for main drive to tank mode
  SetDefaultCommand(new DriveTank());
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
  float left = -LeftSpeed;
  float right = -RightSpeed;

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
  m_Drive->TankDrive(left, right);
}

// Drive robot in Arcade Drive (Constant arc speed around z axis)
// Inputs: XSpeed, ZSpeed - -1 <=speed <= +1.
// -1: full reverse
// 0: full stop
// +1: full forward
void MainDrive::SetArcadeDrive(float XSpeed, float ZSpeed, bool Quickturn)
{

  // make a local copy of parameters so we can check each for range & invert left motor
  float speed = -XSpeed;
  float rotation = ZSpeed;

  // ensure speeds given to us are between -1.0 and 1.0
  if (speed > 1.0)
    speed = 1.0;
  if (speed < -1.0)
    speed = -1.0;

  if (rotation > 1.0)
    rotation = 1.0;
  if (rotation < -1.0)
    rotation = -1.0;

  // drive motors at desired speed and rotation
  m_Drive->ArcadeDrive(speed, rotation, Quickturn);
}

// Drive robot in Curvature Drive (Constant rotational speed around z axis)
// Inputs: XSpeed, ZSpeed - -1 <=speed <= +1.
// -1: full reverse
// 0: full stop
// +1: full forward
void MainDrive::SetCurvatureDrive(float XSpeed, float ZSpeed, bool Quickturn)
{
  // make a local copy of left and right, so we can check each for range & invert left motor
  float speed = -XSpeed;
  float rotation = ZSpeed;

  // ensure speeds given to us are between -1.0 and 1.0
  if (speed > 1.0)
    speed = 1.0;
  if (speed < -1.0)
    speed = -1.0;

  if (rotation > 1.0)
    rotation = 1.0;
  if (rotation < -1.0)
    rotation = -1.0;

  // drive motors at desired speed and rotation
  m_Drive->CurvatureDrive(speed, rotation, Quickturn);
}

// ------------- Drive Encoder Functions -------------

// reset the left encoder to 0 distance
void MainDrive::ResetLeftEncoder(void)
{
  m_EncoderLeft->Reset();
}

// reset the right encoder to 0 value
void MainDrive::ResetRightEncoder(void)
{
  m_EncoderRight->Reset();
}

// get left encoder distance since last reset
float MainDrive::GetLeftEncoderDistance(void)
{
  return m_EncoderLeft->GetDistance();
}

// get right encoder distance since last reset
float MainDrive::GetRightEncoderDistance(void)
{
  return m_EncoderRight->GetDistance();
}
