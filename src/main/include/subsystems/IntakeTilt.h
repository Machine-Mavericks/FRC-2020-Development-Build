/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Intake Tilt subsystem represents the motor drive to control lifting/lowering of the claw or other device on elevator
// The drive consists of a TalonSRX drive with encoder to provide closed loop position control

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include "RobotMap.h"
#include <frc/Shuffleboard/Shuffleboard.h>

using namespace frc;

class IntakeTilt : public frc2::SubsystemBase {
  private:
 
  public:

  // constructor - used to initialize specific hardware
  IntakeTilt();


  // ------------- IntakeTilt Functions -------------


  // Function to command IntakeTilt to move to a fixed position
  void SetIntakeTiltTargetPosition(int pos);

  // Function to return IntakeTilt position
  int GetIntakeTiltTargetPosition(void);

  // Function returns true if IntakeTilt at, or near, its target position
  bool IsIntakeTiltAtTarget(void);

  // initialize position control - to be called when subsystem has been re-homed
  void InitPositionControl();

  // initialize position control - to be called when subsystem has been re-homed
  void InitForHoming(void);
    
  // ------------- Special-Case Functions -------------

  void AdjustforBottomPosition(bool flag);

  // ------------- Encoder-Related Functions -------------

  // Function to command IntakeTilt to move to a fixed position
  void SetIntakeTiltTargetAnalog(int pos);
    
  // Function to get current IntakeTilt target position
  int GetIntakeTiltTargetAnalog(void);

  // Resets IntakeTilt encoder position value
  // USE ONLY WHEN IntakeTilt AT HOME POSITION (BOTTOM?)
  void ResetEncoderPosition(void);

  // Returns IntakeTilt encoder position value (in raw sensor units)
  int GetEncoderPosition(void);


  // ------------- Motor Drive Functions -------------

  // Directly set motor speed to be used for homing 
  void SetMotorSpeed(float speed);

  // Returns motor drive current (amps)
  float GetMotorCurrent(void);

  // Check if forward limit switch is closed
  bool IsFwdLimitSwitchClosed(void);

  // Check if reverse limit switch is closed
  bool IsRevLimitSwitchClosed(void);

  // ------------- Shuffleboard Functions -------------

  void InitializeShuffleBoard(void);
  void UpdateShuffleBoard(void);

  private:

  // define drive motor
  WPI_TalonSRX *m_Motor;

  bool m_AdjustForBottom;

  // Shubbleboard Controls
  nt::NetworkTableEntry MotorEncoder, MotorTarget, MotorCurrent; 
  nt::NetworkTableEntry PosUpAdjust, PosMidAdjust, PosDownAdjust, PosBallAdjust; 
};