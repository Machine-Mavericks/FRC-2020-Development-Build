/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include "RobotMap.h"
#include <frc/Shuffleboard/Shuffleboard.h>

using namespace frc;

class Intake : public frc2::SubsystemBase {
 
 public:

  // constructor - used to initialize specific hardware
  Intake();

  // ------------- Speed Control Functions -------------

  //stop the motors all-together, should you ever want to do that.
  void Stop(void);

  // SetSpeed method used to set the top and bottom speeds of the motors. This is always passed as a pair.
  void SetSpeed(float Speed);

  void SetWristSpeed(float Speed);
  
  // returns motor speeds (in rpm)
  float GetSpeed(void);

  // return motor volts
  float GetVolts(void);

  // return motor current
  float GetCurrent(void);

  // return motor temperature
  float GetTemperature(void);


  // ------------- Shuffleboard Functions -------------

  // initialize shuffleboard controls
  void InitializeShuffleboard(void);

  // update shuffleboard
  void UpdateShuffleboard(void);


  private:
  
  // define drive motors
  WPI_TalonFX *m_IntakeMotor;
  WPI_TalonSRX *m_WristMotor;

  // Shuffleboard Controls
  nt::NetworkTableEntry SpeedSlider;
  nt::NetworkTableEntry MotorSpeed;
  nt::NetworkTableEntry Volts;
  nt::NetworkTableEntry Setting;
  nt::NetworkTableEntry Current;
  nt::NetworkTableEntry Temperature;
};