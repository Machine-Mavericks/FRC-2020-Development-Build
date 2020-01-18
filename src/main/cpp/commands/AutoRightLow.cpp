/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoRightLow.h"
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
#include "robot.h"

AutoRightLow::AutoRightLow() {
  
  //AddParallel(new CameraSwitchPipeline(2));
  AddSequential(new HatchDropOffCargo()); 
  AddParallel(new CameraSwitchPipeline(0));
  
  /*// driver must raise elevator 
  //AddSequential(new ClawOpen());
  AddParallel(new CameraSwitchPipeline(0));
  AddParallel(new TiltUp());
  AddSequential(new DriveTurnToAngle(10.0,1.0,0.5,0.0));
  AddSequential(new DriveStraightDistance(-198, 2.0, 0.8));  // 242
  AddSequential(new DriveTurnToAngle(+90.0, 2.0, 0.5, 0.0));
  AddSequential(new HatchDropOffLow()); */
 
}

// Called once after isFinished returns true
void AutoRightLow::End() {
Robot::m_Limelight.SetPipeline(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoRightLow::Interrupted() {
  End();
}