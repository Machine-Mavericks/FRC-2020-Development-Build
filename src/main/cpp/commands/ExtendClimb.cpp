/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "commands/ExtendClimb.h"
#include "Robot.h"
#include "RobotMap.h"

// Constructor - true tilt down, false tilt up
ExtendClimb::ExtendClimb(bool dir) {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_Climb);

  m_Direction = dir;
}

// Called just before this Command runs the first time
void ExtendClimb::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ExtendClimb::Execute() {
 
  // get robot current direction
  int position = Robot::m_Climb.GetIntakeTiltTargetAnalog();

  if (m_Direction)
  {
      position = position + 200;
      if (position>POS_CLIMBUP)
      position = POS_CLIMBUP;
  }
  else
  {
     position = position - 200;
      if (position <POS_CLIMBDOWN)
      position = POS_CLIMBDOWN; 
  }
  
  // set position target of motor
  Robot::m_Climb.SetIntakeTiltTargetAnalog(position);

}

// Make this return true when this Command no longer needs to run execute()
bool ExtendClimb::IsFinished() {
 // command ends when intake is at target
 int position = Robot::m_Climb.GetIntakeTiltTargetAnalog();
 return ( (m_Direction && position >= POS_CLIMBUP) ||
          ((!m_Direction) && position <= POS_CLIMBDOWN));
}

// Called once after isFinished returns true
void ExtendClimb::End(bool interrupted) {
  
 // hold position
  Robot::m_Climb.SetIntakeTiltTargetAnalog(Robot::m_Climb.GetIntakeTiltTargetAnalog());
  // do nothing - leave intake in position control mode, at its current target setting
}