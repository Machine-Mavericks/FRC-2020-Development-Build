/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TiltHome.h"
#include "Robot.h"
#include "subsystems/IntakeTilt.h"

// Constructor for TiltHome command
TiltHome::TiltHome() {
  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_IntakeTilt);

  // tank drive command is interruptable
  SetInterruptible(false);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);

  m_Finished=false;
  m_Time=0.0;
}

// Called just before this Command runs the first time
void TiltHome::Initialize() {
  // initialize for homing
  Robot::m_IntakeTilt.InitForHoming();
  
  // turn on motor to move tilt towards home position
  Robot::m_IntakeTilt.SetMotorSpeed(-0.20);

  // command is not finished util proven otherwise
  m_Finished = false;
  
  // reset timer
  m_Time = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void TiltHome::Execute() {

  // increment timer
  m_Time += 0.02;

  // we are finished when home limit switch is detected closed or time has exceeded 10s
  if (m_Time > 0.5)
    m_Finished = true;
}


// Make this return true when this Command no longer needs to run execute()
bool TiltHome::IsFinished() {   
  return m_Finished;
}

// Called once after isFinished returns true
void TiltHome::End() {

  // stop motor
  Robot::m_IntakeTilt.SetMotorSpeed(0);

  //reset encoder
  Robot::m_IntakeTilt.InitPositionControl();
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void TiltHome::Interrupted() {}
