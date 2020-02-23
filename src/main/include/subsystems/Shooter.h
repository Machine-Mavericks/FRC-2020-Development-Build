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

class Shooter : public frc2::SubsystemBase {
 
 public:

  // constructor - used to initialize specific hardware
  Shooter();

  // ------------- Speed Control Functions -------------

  //stop the motors all-together, should you ever want to do that.
  void Stop(void);

  // SetSpeed method used to set the top and bottom speeds of the motors. This is always passed as a pair.
  void SetSpeed(double TopSpeed, double BottomSpeed);
  
  // returns motor speeds (in rpm)
  float GetTopSpeed(void);
  float GetBottomSpeed(void);

  // return motor volts
  float GetTopVolts(void);
  float GetBottomVolts(void);

  // return motor current
  float GetTopCurrent(void);
  float GetBottomCurrent(void);

  // ------------- Shuffleboard Functions -------------

  // initialize shuffleboard controls
  void InitializeShuffleboard(void);

  // update shuffleboard
  void UpdateShuffleboard(void);


  private:
  
  // define drive motors - assign each to specific PWN channel
  WPI_TalonFX *m_MotorTop;
  WPI_TalonFX *m_MotorBottom;

  // Shuffleboard Controls
  nt::NetworkTableEntry Speed;
  nt::NetworkTableEntry TopVolts, BottomVolts; 
  nt::NetworkTableEntry TopSpeed, BottomSpeed;
  nt::NetworkTableEntry TopSetting, BottomSetting;
  nt::NetworkTableEntry TopCurrent, BottomCurrent;
};