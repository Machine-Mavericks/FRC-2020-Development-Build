/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClawOpen.h"
#include "Robot.h"
#include "RobotMap.h"

// default position is open
static int position = CLAW_OPEN_POSITION;

ClawOpen::ClawOpen() {
  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_Claw);

  // command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void ClawOpen::Initialize() {

  // set Claw target position
  Robot::m_Claw.SetClawTargetPosition(1);
}

// Called repeatedly when this Command is scheduled to run
void ClawOpen::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ClawOpen::IsFinished() {
  return Robot::m_Claw.IsClawAtTarget(); }

// Called once after isFinished returns true
void ClawOpen::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClawOpen::Interrupted() {}
