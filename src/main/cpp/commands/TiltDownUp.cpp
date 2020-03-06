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
TiltDownUp::TiltDownUp(TiltPosition pos) {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_IntakeTilt);

  // record if we are to turn on/off intake
  m_TargetPosition = pos;
}

// Called just before this Command runs the first time
void TiltDownUp::Initialize() {
  
}

// Called repeatedly when this Command is scheduled to run
void TiltDownUp::Execute() {
 
  // get robot current direction
  int position = Robot::m_IntakeTilt.GetIntakeTiltTargetAnalog();

  // if target is all way up 
  if (m_TargetPosition == TiltPosition::TiltUp)
  {
    position = position - 200;
    if (position <=POS_TILTUP)
      position = POS_TILTUP;
  }

  // if target is mid-way for ball dispenser pickup
  else if (m_TargetPosition ==  TiltPosition::TiltMid)
  {
    if (position < POS_TILTMID) {
      position = position + 200;
      if (position >POS_TILTMID) position = POS_TILTMID;
    }
    else if (position > POS_TILTMID) {
      position = position - 200;
      if (position <POS_TILTMID) position = POS_TILTMID;
    }
  }

  // if target is down for ball floor pickup
  else if (m_TargetPosition == TiltPosition::TiltDown)
  {
    position = position + 200;
    if (position >=POS_TILTDOWN)
    position = POS_TILTDOWN;
  }


  // set position target of motor
  Robot::m_IntakeTilt.SetIntakeTiltTargetAnalog(position);

}

// Make this return true when this Command no longer needs to run execute()
bool TiltDownUp::IsFinished() {
 
 // command ends when intake is at target
 int position = Robot::m_IntakeTilt.GetIntakeTiltTargetAnalog();
 return ( (m_TargetPosition==0 && position <= POS_TILTUP) ||
          (m_TargetPosition==1 && position == POS_TILTMID) ||
          (m_TargetPosition==2 && position >= POS_TILTDOWN));

}

// Called once after isFinished returns true
void TiltDownUp::End(bool interrupted) {
  
  // do nothing - leave intake in position control mode, at its current target setting
}