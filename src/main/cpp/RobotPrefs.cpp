/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotPrefs.h"
#include "RobotMap.h"


// constructor - initializes preferences
RobotPrefs::RobotPrefs(void)
{
  // get pointer to robot preferences
  prefs = Preferences::GetInstance();
}

// Reset settings to defaults defined in RobotMap
void RobotPrefs::ResetToDefaults(void)
{
  // clear all preferences
  prefs->RemoveAll();
  
  // Set Elevator defaults
  prefs->PutInt("ELV-SOFTMIN", ELEVATOR_SOFT_LIMIT_MIN);
  prefs->PutInt("ELV-SOFTMAX", ELEVATOR_SOFT_LIMIT_MAX);
  prefs->PutInt("ELV-POS0", ELEVATOR_POSITION0);
  prefs->PutInt("ELV-POS1", ELEVATOR_POSITION1);
  prefs->PutInt("ELV-POS2", ELEVATOR_POSITION2);
  prefs->PutInt("ELV-POS3", ELEVATOR_POSITION3);
  prefs->PutInt("ELV-POS4", ELEVATOR_POSITION4);

  // Set Tilt defaults
  prefs->PutInt("TLT-SOFTMIN", TILT_SOFT_LIMIT_MIN);
  prefs->PutInt("TLT-SOFTMAX", TILT_SOFT_LIMIT_MAX);
  prefs->PutInt("TLT-POS0", ELEVATOR_POSITION0);
  prefs->PutInt("TLT-POS1", ELEVATOR_POSITION1);
  prefs->PutInt("TLT-POS2", ELEVATOR_POSITION2);
}

// individual accessors - allows read-only access to settings 
const int RobotPrefs::ElevatorSoftMin() { return prefs->GetInt("ELV-SOFTMIN", ELEVATOR_SOFT_LIMIT_MIN); }
const int RobotPrefs::ElevatorSoftMax() { return prefs->GetInt("ELV-SOFTMAX", ELEVATOR_SOFT_LIMIT_MAX); }
const int RobotPrefs::ElevatorPos0() { return prefs->GetInt("ELV-POS0", ELEVATOR_POSITION0); }
const int RobotPrefs::ElevatorPos1() { return prefs->GetInt("ELV-POS1", ELEVATOR_POSITION1); }
const int RobotPrefs::ElevatorPos2() { return prefs->GetInt("ELV-POS2", ELEVATOR_POSITION2); }
const int RobotPrefs::ElevatorPos3() { return prefs->GetInt("ELV-POS3", ELEVATOR_POSITION3); }
const int RobotPrefs::ElevatorPos4() { return prefs->GetInt("ELV-POS4", ELEVATOR_POSITION4); }

const int RobotPrefs::TiltSoftMin() { return prefs->GetInt("TLT-SOFTMIN", TILT_SOFT_LIMIT_MIN); }
const int RobotPrefs::TiltSoftMax() { return prefs->GetInt("TLT-SOFTMIN", TILT_SOFT_LIMIT_MAX); }
const int RobotPrefs::TiltPos0() { return prefs->GetInt("TLT-POS0", TILT_UP_POSITION); }
const int RobotPrefs::TiltPos1() { return prefs->GetInt("TLT-POS1", TILT_MID_POSITION); }
const int RobotPrefs::TiltPos2() { return prefs->GetInt("TLT-POS2", TILT_DOWN_POSITION); }


