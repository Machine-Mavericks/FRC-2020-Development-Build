/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Elevator subsystem represents the motor drive to control lifting/lowering of the elevator
// The elevator drive consists of a TalonSRX drive with encoder to provide closed loop position control

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/Shuffleboard/Shuffleboard.h>

using namespace frc;

class Elevator : public frc::Subsystem {
  
  public:

  // constructor - used to initialize specific hardware
  Elevator();

  // default command to run with the subsystem
  void InitDefaultCommand() override;

    
  // ------------- Elevator Functions -------------

  // Function to command elevator to move to a fixed position
  void SetElevatorPresetPosition(int pos);

  // Function to return elevator position
  int GetElevatorTargetPresetPosition(void);

  // Function to return elevator's next preset position (next higher position)
  int GetElevatorNextHigherPresetPosition(void);
  int GetElevatorNextLowerPresetPosition(void); 

  // Function returns true if elevator at, or near, its target position
  bool IsElevatorAtTarget(void);


  // ------------- Encoder-Related Functions -------------


  // Function to command elevator to move to a fixed position
  void SetElevatorTargetAnalog(int pos);
    
  // Function to get current elevator target position
  int GetElevatorTargetAnalog(void);

  // Resets elevator encoder position value
  // USE ONLY WHEN ELEVATOR AT HOME POSITION (BOTTOM?)
  void ResetEncoderPosition(void);

  // Returns elevator encoder position value (in raw sensor units)
  int GetEncoderPosition(void);

  // Returns elevator encoder speed value (in raw sensor units per 100ms)
  int GetEncoderSpeed(void);

   
  // ------------- Motor Drive Functions -------------

  // Returns motor drive current (amps)
  float GetMotorCurrent(void);

  // Check if forward limit switch is closed
  bool IsFwdLimitSwitchClosed(void);

  // Check if reverse limit switch is closed
  bool IsRevLimitSwitchClosed(void);

  // ------------- Shuffleboard Functions -------------

  void InitializeShuffleBoard(void);

  // update shuffle board with current drive values
  void UpdateShuffleBoard(void);

  private:

  // define drive motor
  WPI_TalonSRX *m_Motor1;
  WPI_VictorSPX *m_Motor2;
 
  // Shubbleboard Controls
  nt::NetworkTableEntry MotorEncoder, MotorTarget, MotorCurrent; 

};