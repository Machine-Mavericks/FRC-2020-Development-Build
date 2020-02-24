/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// SteerTowardsTarget drive command allows robot to be driven in SteerTowardsTarget mode.
// This is the default command when robot in teleop mode

#include "commands/IntakeOnOff.h"
#include "Robot.h"
#include "RobotMap.h"

// Constructor - true to turn on, false to turn off
IntakeOnOff::IntakeOnOff(bool On) {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_Intake);

  // record if we are to turn on/off intake
  m_IntakeOn = On;
}

// Called just before this Command runs the first time
void IntakeOnOff::Initialize() {
  if (m_IntakeOn)
    Robot::m_Intake.SetSpeed(Robot::m_Intake.GetSpeedSliderValue());
  else
    Robot::m_Intake.SetSpeed(0);
}

// Called repeatedly when this Command is scheduled to run
void IntakeOnOff::Execute() {
 
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeOnOff::IsFinished() {
  return true;
}

// Called once after isFinished returns true
void IntakeOnOff::End(bool interrupted) {
}