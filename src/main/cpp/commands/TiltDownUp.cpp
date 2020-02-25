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
  
  /*int position = Robot::m_IntakeTilt.GetIntakeTiltTargetAnalog();
  
  if (m_Direction)
    position += 1000;
  else
    position -= 1000;

  Robot::m_IntakeTilt.SetIntakeTiltTargetAnalog(position);
  */
}

// Called repeatedly when this Command is scheduled to run
void TiltDownUp::Execute() {
 
int position = Robot::m_IntakeTilt.GetIntakeTiltTargetAnalog();

if (m_Direction)
  position = position + 50;
else
  position = position - 50;

if (position <=0)
  position = 0;
if (position >=12400)
  position = 12400;

Robot::m_IntakeTilt.SetIntakeTiltTargetAnalog(position);

}

// Make this return true when this Command no longer needs to run execute()
bool TiltDownUp::IsFinished() {
 
 int position = Robot::m_IntakeTilt.GetIntakeTiltTargetAnalog();
 return ((m_Direction && position >=14000) ||
         (!m_Direction && position <=0));

}

// Called once after isFinished returns true
void TiltDownUp::End(bool interrupted) {
 //Robot::m_IntakeTilt.m_Motor->SetIntegralAccumulator(0.0, 0, 0);
 //Robot::m_IntakeTilt.m_Motor->Set(ControlMode::PercentOutput,0.0);

  
}