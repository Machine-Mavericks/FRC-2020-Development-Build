/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClawGrabBall.h"
#include "Robot.h"
#include "RobotMap.h"

// default position is open
static int position = CLAW_BALL_POSITION;

ClawGrabBall::ClawGrabBall() {
  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_Claw);

  // tank drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void ClawGrabBall::Initialize() {

  // set Claw target position
  Robot::m_Claw.SetClawTargetPosition(0); 
  
}

// Called repeatedly when this Command is scheduled to run
void ClawGrabBall::Execute() {

  // move claw to position
  Robot::m_Claw.SetClawTargetPosition(0);
}

// Make this return true when this Command no longer needs to run execute()
bool ClawGrabBall::IsFinished() {
  return Robot::m_Claw.IsClawAtTarget(); }

// Called once after isFinished returns true
void ClawGrabBall::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClawGrabBall::Interrupted() {}
