/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SnowblowerOut.h"
#include "Robot.h"
#include "RobotMap.h"

// Constructs snowblower Out command
SnowblowerOut::SnowblowerOut() {

  // This command requires the snow blower
  Requires (&Robot::m_Snowblower);

  // tank drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void SnowblowerOut::Initialize() {
    
    // set timer to 0
    timer = 0;
    
    // set motor current
    Robot::m_Snowblower.SetMaxMotorCurrent(SNOWBLOWER_CURRENT_LIMIT_OUT);

    // set motor speed
    Robot::m_Snowblower.SetMotorSpeed(1.0);
}


// Called repeatedly when this Command is scheduled to run
void SnowblowerOut::Execute() {
    timer = timer + 0.02;
}

// Make this return true when this Command no longer needs to run execute()
bool SnowblowerOut::IsFinished() {
    if (timer >= 3.0)
        return true;
    else
        return false;
 }

// Called once after isFinished returns true
void SnowblowerOut::End() {
    Robot::m_Snowblower.SetMotorSpeed(0.0);
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void SnowblowerOut::Interrupted() {}