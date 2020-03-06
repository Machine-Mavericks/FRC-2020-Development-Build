/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "commands/Agitate.h"
#include "Robot.h"
#include "RobotMap.h"

// Constructor
Agitate::Agitate() {
  // Use AddRequirements here to declare subsystem dependencies 
  AddRequirements(&Robot::m_Agitator);
}

// Called just before this Command runs the first time
void Agitate::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Agitate::Execute() {
 
  // get robot current direction
    Robot::m_Agitator.Start();// Robot::m_Agitate.GetIntakeTiltTargetAnalog();


}

// Make this return true when this Command no longer needs to run execute()
bool Agitate::IsFinished() {
    return false;
 
}

// Called once after isFinished returns true
void Agitate::End(bool interrupted) {
  
 // hold position
  Robot::m_Agitator.Stop();
}