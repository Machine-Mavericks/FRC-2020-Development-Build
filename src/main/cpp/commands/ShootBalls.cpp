/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// SteerTowardsTarget drive command allows robot to be driven in SteerTowardsTarget mode.
// This is the default command when robot in teleop mode

#include "commands/ShootBalls.h"
#include "Robot.h"
#include "RobotMap.h"

ShootBalls::ShootBalls() {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_Shooter);
}

// Called just before this Command runs the first time
void ShootBalls::Initialize() {
  
  
  //m_ShooterSpeed = Robot::m_Shooter.GetSpeedSliderValue();
  m_UpliferSpeed = Robot::m_Uplifter.GetSpeedSliderValue();

  // set shooter speed
  //Robot::m_Shooter.SetSpeed (m_ShooterSpeed, -m_ShooterSpeed);

  m_SpeedUpTime = 0.0;
  m_ShootTime = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void ShootBalls::Execute() {
 
  if (m_SpeedUpTime < 1.0)
    m_SpeedUpTime += 0.02;
  else
  {
    Robot::m_Uplifter.SetSpeed(m_UpliferSpeed);
    m_ShootTime += 0.02;
  }

}

// Make this return true when this Command no longer needs to run execute()
bool ShootBalls::IsFinished() {
   return (m_ShootTime > 3.0);
}

// Called once after isFinished returns true
void ShootBalls::End(bool interrupted) {
    // switch off ball lifter mechanism
    Robot::m_Uplifter.SetSpeed(0.0);
    
    // return shooter to idle speed
    //Robot::m_Shooter.SetSpeed(Robot::m_Shooter.GetIdleSpeedSliderValue());
}