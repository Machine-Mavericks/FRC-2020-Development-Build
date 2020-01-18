/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoRunLeftFront.h"
#include "Robot.h"
#include "commands/DriveStraightDistance.h"
#include "commands/DriveTurnToAngle.h"
#include "commands/TiltUp.h"
#include "commands/CameraSwitchPipeline.h"
#include "commands/DriveGoToTarget.h"
#include "commands/ClawOpen.h"
#include "commands/TiltMid.h"
#include "commands/HatchDropOffCargo.h"
#include "commands/DriveFollowPath.h"
#include "commands/HatchPickup.h"
#include "commands/ElevatorGoToEncoder.h"
#include "commands/TimeDelay.h"

AutoRunLeftFront::AutoRunLeftFront() {
  
  //AddParallel(new CameraSwitchPipeline(3));
  AddParallel(new TiltUp());
  AddSequential(new DriveStraightDistance(72  , 6.0, 0.35));
  AddParallel(new ElevatorGoToEncoder(5000));
  AddSequential(new TimeDelay(0.5));
  AddParallel(new ElevatorGoToEncoder(0));
  AddSequential(new TimeDelay(0.5));
  AddSequential(new HatchDropOffCargo());
  AddParallel(new CameraSwitchPipeline(0));
}

// Called once after isFinished returns true
void AutoRunLeftFront::End() {
  Robot::m_Limelight.SetPipeline(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoRunLeftFront::Interrupted() {
  End();
}