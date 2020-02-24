/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// SteerTowardsTarget drive command allows robot to be driven in SteerTowardsTarget mode.
// This is the default command when robot in teleop mode

#include "commands/ShooterSetIdle.h"
#include "Robot.h"
#include "RobotMap.h"

ShooterSetIdle::ShooterSetIdle() {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_Shooter);
}

// Called just before this Command runs the first time
void ShooterSetIdle::Initialize() {
    
    // get idle speed from shuffleboard and set shooter speed
    float IdleSpeed = Robot::m_Shooter.GetIdleSpeedSliderValue();
    Robot::m_Shooter.SetSpeed(IdleSpeed);
 }

// Called repeatedly when this Command is scheduled to run
void ShooterSetIdle::Execute() { }

// Make this return true when this Command no longer needs to run execute()
bool ShooterSetIdle::IsFinished() {
   return true;
}

// Called once after isFinished returns true
void ShooterSetIdle::End(bool interrupted) { }