/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HatchDropOffLow.h"
#include "commands/TiltMid.h"
#include "commands/TiltUp.h"
#include "commands/TiltDown.h"
#include "commands/FollowTargetTilStopped.h"
#include "commands/ElevatorGoToEncoder.h"
#include "commands/TimeDelay.h"
#include "commands/DriveStraightTilStopped.h"
#include "commands/DriveStraightDistance.h"
#include "commands/FollowTargetTillStopped2.h"

HatchDropOffLow::HatchDropOffLow() {
  
  // Revised hatch drop-off technique April 6 2019
  AddSequential(new ElevatorGoToEncoder(0));
  AddSequential(new TiltUp());
  AddSequential(new FollowTargetTilStopped2(0.4, false));
  AddSequential(new DriveStraightDistance(-5, 2, 0.25));  // new // was 1"
  AddSequential(new TiltDown()); 
  AddSequential(new TimeDelay(0.5));
  AddSequential(new DriveStraightTilStopped(-48.0,0.5));
  AddParallel(new TiltUp());

  // Old hatch drop-off technique
  //AddSequential(new TiltMid());
  //AddSequential(new ElevatorGoToEncoder(14151));//(12651));
  //AddSequential(new FollowTargetTilStopped(0.35));
  //AddSequential(new ElevatorGoToEncoder(2192)); //(3692));
  //AddSequential(new TimeDelay(0.3));
  //AddSequential(new DriveStraightTilStopped(-15.0,0.5));
  //AddParallel(new TiltUp());
}
