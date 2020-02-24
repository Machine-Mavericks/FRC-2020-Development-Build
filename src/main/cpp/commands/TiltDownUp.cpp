/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// SteerTowardsTarget drive command allows robot to be driven in SteerTowardsTarget mode.
// This is the default command when robot in teleop mode

#include "commands/TiltDownUp.h"
#include "Robot.h"
#include "RobotMap.h"

// Constructor - true tilt down, false tilt up
TiltDownUp::TiltDownUp(bool dir) {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_IntakeTilt);

  // record if we are to turn on/off intake
  m_Direction = dir;
}

// Called just before this Command runs the first time
void TiltDownUp::Initialize() {
  
  // get position of tilting
  int position = Robot::m_IntakeTilt.GetIntakeTiltTargetPosition();

  if (m_Direction)
    Robot::m_IntakeTilt.SetIntakeTiltTargetPosition(position+1);
  else
    Robot::m_IntakeTilt.SetIntakeTiltTargetPosition(position-1);
}

// Called repeatedly when this Command is scheduled to run
void TiltDownUp::Execute() {
 
}

// Make this return true when this Command no longer needs to run execute()
bool TiltDownUp::IsFinished() {
  return true;
}

// Called once after isFinished returns true
void TiltDownUp::End(bool interrupted) {
}