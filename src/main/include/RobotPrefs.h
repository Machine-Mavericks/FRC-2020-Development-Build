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

};