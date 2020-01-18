/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SnowblowerOff.h"
#include "Robot.h"
#include "RobotMap.h"

// Constructs snowblower Off command
SnowblowerOff::SnowblowerOff() {

  // This command requires the snow blower
  Requires (&Robot::m_Snowblower);

  // tank drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void SnowblowerOff::Initialize() {
        
    // set motor current
    Robot::m_Snowblower.SetMaxMotorCurrent(SNOWBLOWER_CURRENT_LIMIT_IN);

    // set motor speed
    Robot::m_Snowblower.SetMotorSpeed(0.0);
}


// Called repeatedly when this Command is scheduled to run
void SnowblowerOff::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool SnowblowerOff::IsFinished() {
    return true;
 }

// Called once after isFinished returns true
void SnowblowerOff::End() {
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void SnowblowerOff::Interrupted() {}