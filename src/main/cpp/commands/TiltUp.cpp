/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TiltUp.h"
#include "Robot.h"
#include "RobotMap.h"

// default position is open
static int position = TILT_UP_POSITION;

TiltUp::TiltUp() {
  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_IntakeTilt);

  // tank drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void TiltUp::Initialize() {

  // set IntakeTilt target position
  Robot::m_IntakeTilt.SetIntakeTiltTargetPosition(0); 
  
}

// Called repeatedly when this Command is scheduled to run
void TiltUp::Execute() {

  // move IntakeTilt to position
 // Robot::m_IntakeTilt.SetMotorSpeed(1.0);
  Robot::m_IntakeTilt.SetIntakeTiltTargetPosition(0);
}

// Make this return true when this Command no longer needs to run execute()
bool TiltUp::IsFinished() {
  return true;
  //return Robot::m_IntakeTilt.IsIntakeTiltAtTarget(); 
  }

// Called once after isFinished returns true
void TiltUp::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TiltUp::Interrupted() {}
