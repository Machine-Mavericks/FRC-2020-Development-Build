/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HatchPickup.h"
#include "commands/TiltDown.h"
#include "commands/TiltUp.h"
#include "commands/FollowTargetTilStopped.h"
#include "commands/ElevatorGoToEncoder.h"
#include "commands/TimeDelay.h"
#include "commands/DriveStraightTilStopped.h"
#include "commands/DriveStraightDistance.h"
#include "commands/FollowTargetTillStopped2.h"
//24124

HatchPickup::HatchPickup() {
  // lower wrist and drive forward to human player station
  AddSequential(new TiltDown());
  AddSequential(new ElevatorGoToEncoder(3000));
  AddSequential(new FollowTargetTilStopped2(0.5, true));
  AddSequential(new ElevatorGoToEncoder(20000.0));
  AddSequential(new TimeDelay(1.0));
  AddParallel(new TiltUp());
  AddSequential(new DriveStraightDistance(-60.0,5, 0.2));
  //AddSequential(new DriveStraightTilStopped(-30.0,0.2));
 

}
