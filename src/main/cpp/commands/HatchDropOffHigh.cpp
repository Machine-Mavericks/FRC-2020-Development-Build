/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HatchDropOffHigh.h"
#include "commands/TiltMid.h"
#include "commands/TiltUp.h"
#include "commands/FollowTargetTilStopped.h"
#include "commands/ElevatorGoToEncoder.h"
#include "commands/TimeDelay.h"
#include "commands/DriveStraightTilStopped.h"
#include "commands/DriveStraightDistance.h"
#include "commands/FollowTargetTillStopped2.h"
//24124

HatchDropOffHigh::HatchDropOffHigh() {
  // lower wrist and drive forward to human player station
  AddSequential(new TiltUp());
  AddSequential(new ElevatorGoToEncoder(0));//(12651));
  AddSequential(new FollowTargetTilStopped2(0.4, false));
  AddSequential(new DriveStraightDistance(-5, 1, 0.25));
  AddSequential(new ElevatorGoToEncoder(64900));//(12651));
  AddSequential(new TimeDelay(3.35));
  AddSequential(new TiltMid());
  AddSequential(new TimeDelay(1.0));
  AddSequential(new ElevatorGoToEncoder(52000)); //(3692));
  AddSequential(new TimeDelay(1.0));
  AddSequential(new DriveStraightTilStopped(-15.0,0.5));
  AddParallel(new TiltUp());

}
 