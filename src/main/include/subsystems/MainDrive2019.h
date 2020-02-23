/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#pragma once

#include <frc/SpeedControllerGroup.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>
#include "RobotMap.h"
#include <frc/Encoder.h>
#include <frc/Shuffleboard/Shuffleboard.h>
#include <frc2/command/SubsystemBase.h>
#include "frc/kinematics/DifferentialDriveWheelSpeeds.h"
#include <units/units.h>

using namespace frc;


class MainDrive2019 : public frc2::SubsystemBase {

public:

  // constructor - used to initialize specific hardware
  MainDrive2019();

  // Drive in Tank Drive - where left and right motors are driven independently
  void SetTankDrive(float LeftSpeed, float RightSpeed);

  // Drive robot in Arcade Drive (Constant arc speed around z axis)
  void SetArcadeDrive(float XSpeed, float ZRotation, bool Quickturn);
 

  // ------------- Voltage Compentation -------------


  // maximum voltage guaranteed by battery - used for linear motor control
  const float MAXVOLTS = 12.0;

  // set/get motor voltage compenstation level for linear performance
  void SetVoltageCompensationEnable (bool enable);
  void SetVoltageCompensationLevel (float volts);
  float GetVoltageCompenstationLevel (void);


  // ------------- Distance / Speed Functions -------------

  // get left/right encoder distance since last reset
  float GetLeftEncoderDistance(void); 
  float GetRightEncoderDistance(void);

  // get right/left encoder speed 
  float GetRightEncoderSpeed(void);
  float GetLeftEncoderSpeed(void);


  // ------------- Functions Required by Tractory Control -------------
 

  // set motor volages for tank mode - inputs left/right volts
  void SetTankDriveVolts(units::volt_t left, units::volt_t right);

  // return left/right drive speed (in m/s)
  DifferentialDriveWheelSpeeds GetWheelSpeeds(void);

  // functions to return current motor voltage
  float GetFrontLeftMotorVoltage(void);
  float GetRearLeftMotorVoltage(void);
  float GetFrontRightMotorVoltage(void);
  float GetRearRightMotorVoltage(void);


  // ------------- Drive Encoder Functions -------------


  // reset the left /right encoders
  void ResetLeftEncoder(void);
  void ResetRightEncoder(void);

  // returns motor encoder values (in raw units)
  int GetLeftEncoderTicks(void);
  int GetRightEncoderTicks(void);


  // ------------- Throttle Control -------------


  // returns position of throttle control on shuffleboard - if not available, returns 1.0
  float GetThrottle(void);


  // ------------- Tank Control Mode -------------

  // returns true if shuffleboard switch indicates robot to be in tank mode
  bool GetTankMode(void);

  // ------------- Access to Motors -------------


  // returns pointers to motors
  WPI_VictorSPX *GetFrontLeftMotor (void);
  WPI_VictorSPX *GetRearLeftMotor (void);
  WPI_VictorSPX *GetFrontRightMotor (void);
  WPI_VictorSPX *GetRearRightMotor (void);


  // ------------- Shuffleboard Functions -------------

  void InitializeShuffleBoard(void);
  void UpdateShuffleBoard(void);


  private:
  
  // define drive motors - assign each to specific PWN channel
  WPI_VictorSPX *m_MotorFrontLeft;
  WPI_VictorSPX *m_MotorRearLeft;
  WPI_VictorSPX *m_MotorFrontRight;
  WPI_VictorSPX *m_MotorRearRight;

  // current motor compenstation level
  float m_VoltageCompenstationLevel;

  // create overall drive system
  DifferentialDrive *m_Drive;

  // encoder scaling factor (convert from encoder ticks to distance (m))
  // 0.074903 = measured scaling factor for gearing ratio
  const float EncoderScaleFactor = (kPi * 0.0254 * WHEEL_DIAMETER) / (float)ENCODER_PULSE_PER_REVOLUTION;

  // create encoder objects
  Encoder *m_EncoderRight;
  Encoder *m_EncoderLeft;

  // Shubbleboard Controls
  nt::NetworkTableEntry LeftDistance, RightDistance; 
  nt::NetworkTableEntry LeftSpeed, RightSpeed;
  nt::NetworkTableEntry LeftEncoder, RightEncoder;
  nt::NetworkTableEntry LeftFrontVolts, LeftRearVolts, RightFrontVolts, RightRearVolts;
  nt::NetworkTableEntry Throttle;
  nt::NetworkTableEntry TankMode;
};


