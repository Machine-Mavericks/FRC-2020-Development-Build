/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Robot Preferences class holds all the robot preferences which are saved to robot flash
// memory and can be edited by the smart dashboard.

#pragma once

#include "frc/Preferences.h"

using namespace frc;

class RobotPrefs {
  private:
  
  // robot preferences
  Preferences *prefs;

  public:
  // constructor - initializes preferences
  RobotPrefs(void);

  // Reset settings to default
  void ResetToDefaults(void);

  // individual accessors - allows read-only access to settings 
  const int ElevatorSoftMin();
  const int ElevatorSoftMax();
  const int ElevatorPos0();
  const int ElevatorPos1();
  const int ElevatorPos2();
  const int ElevatorPos3();
  const int ElevatorPos4();


  const int TiltSoftMin();
  const int TiltSoftMax();
  const int TiltPos0();
  const int TiltPos1();
  const int TiltPos2();
};