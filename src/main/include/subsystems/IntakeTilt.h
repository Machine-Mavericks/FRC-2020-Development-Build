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


// Tilting position constants
#define TILT_UP_POSITION        0
#define TILT_MID_POSITION       7000
#define TILT_DOWN_POSITION      14000
    
// Tilting position soft limits
#define TILT_SOFT_LIMIT_MAX     11560
#define TILT_SOFT_LIMIT_MIN     0

// Tilting PID gains
#define TILT_PGAIN              0.15      // = 0.15 Feb 24/2020 - worked ok, on edge of unstable near top motion of arm
#define TILT_IGAIN              0.0002    // = 0.0002 
#define TILT_DGAIN              0         // = 0 

#define TILT_MAX_INTEGRAL_ACCUMULATOR       1000000
#define TILT_ALLOWABLE_CLOSEDLOOP_ERROR     100

#define INTAKETILT_DRIVE_MAXRAMP    0.02



class IntakeTilt : public frc2::SubsystemBase {
 
 public:

  // constructor - used to initialize specific hardware
  IntakeTilt();


  // ------------- Encoder-Related Functions -------------

  // Resets IntakeTilt encoder position value
  // USE ONLY WHEN IntakeTilt AT HOME POSITION
  void ResetEncoderPosition(void);

  // Returns IntakeTilt encoder position value (in raw sensor units)
  int GetEncoderPosition(void);

  // Function to command IntakeTilt to move to a fixed position
  void SetIntakeTiltTargetAnalog(int pos);
    
  // Function to get current IntakeTilt target position
  int GetIntakeTiltTargetAnalog(void);


  // ------------- Motor-Related Functions -------------


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

 // define drive motors
  WPI_TalonFX *m_Motor;

  private:
  
 
  
  // Shuffleboard Controls
  nt::NetworkTableEntry MotorEncoder, MotorTarget;
  nt::NetworkTableEntry PosUpAdjust, PosMidAdjust, PosDownAdjust; 
  nt::NetworkTableEntry Volts;
  nt::NetworkTableEntry Current;
  nt::NetworkTableEntry Temperature;

};