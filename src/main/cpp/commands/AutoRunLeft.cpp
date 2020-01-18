/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoRunLeft.h"
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

AutoRunLeft::AutoRunLeft() {
  

  // require to add 18" for competition game
  AddParallel(new CameraSwitchPipeline(2));
  AddParallel(new TiltUp());
  AddSequential(new DriveStraightDistance(-114  , 1.0, 0.4));   // 1"  0.3 // was 96 for kingston
  AddParallel(new ElevatorGoToEncoder(5000));
  AddSequential(new DriveTurnToAngle(-30.0, 3.0, 1.0, 0.0));
  AddSequential(new DriveStraightDistance(-131  , 1.0, 0.6));  
  AddParallel(new ElevatorGoToEncoder(0));
  AddSequential(new DriveTurnToAngle(-90.0, 5.0, 0.5, 0.0));  // 1 deg
  AddSequential(new HatchDropOffCargo()); 

  //AddParallel(new CameraSwitchPipeline(2));
  //AddParallel(new TiltUp());
  //AddSequential(new DriveTurnToAngle(-10.0,1.0,0.5,0.0));
  //AddSequential(new DriveStraightDistance(-238, 2.0, 0.8));  // 246 April 8
  //AddSequential(new DriveTurnToAngle(-90.0, 2.0, 0.5, 0.0));
  //AddSequential(new HatchDropOffLow());
  //AddSequential(new CameraSwitchPipeline(0));

}

// Called once after isFinished returns true
void AutoRunLeft::End() {
Robot::m_Limelight.SetPipeline(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoRunLeft::Interrupted() {
  End();
}