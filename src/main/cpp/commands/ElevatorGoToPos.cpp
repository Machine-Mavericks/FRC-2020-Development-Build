/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorGoToPos.h"
#include "Robot.h"
#include "RobotMap.h"

// Move elevator up or down one position
// Inputs: true is up, false is down
ElevatorGoToPos::ElevatorGoToPos(int position) {
  // This command requires both elevator and intake tilt
  // Intake tilt is adjusted based on elevator target position
  Requires (&Robot::m_Elevator);
  Requires (&Robot::m_IntakeTilt);

  // tank drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);

    // set position
    pos = position;
}

// Called just before this Command runs the first time
void ElevatorGoToPos::Initialize() {
   
  // Assume elevator is not being moded to bottom position
  // Inform intake tilt accoringly, so it holds horizontal
  Robot::m_IntakeTilt.AdjustforBottomPosition(false);
  
  
  //Robot::m_Elevator.SetElevatorTargetAnalog(pos);
  Robot::m_Elevator.SetElevatorPresetPosition(pos);


  }


// Called repeatedly when this Command is scheduled to run
void ElevatorGoToPos::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorGoToPos::IsFinished() { 
  return Robot::m_Elevator.IsElevatorAtTarget();
  
 }

// Called once after isFinished returns true
void ElevatorGoToPos::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorGoToPos::Interrupted() {}
