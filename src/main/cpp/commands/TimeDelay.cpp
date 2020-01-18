/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TimeDelay.h"

TimeDelay::TimeDelay(double timeout)
    : TimedCommand(timeout) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void TimeDelay::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TimeDelay::Execute() {}

// Called once after command times out
void TimeDelay::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimeDelay::Interrupted() {}