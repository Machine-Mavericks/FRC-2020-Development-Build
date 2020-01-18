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
  

}



