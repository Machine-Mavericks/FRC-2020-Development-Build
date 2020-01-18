/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LH2R.h"
#include "commands/DriveGoToTarget.h"
#include "commands/DriveStraightDistance.h"
#include "commands/DriveTurnToAngle.h"
#include "commands/ClawOpen.h"

LH2R::LH2R() {
  AddSequential(new ClawOpen());
  AddSequential(new DriveStraightDistance(-35.0,1.0, 0.5));
  AddSequential(new DriveTurnToAngle(145.0,5.0,0.3,0.40));
   //AddSequential(new DriveStraightDistance(-12.0,1.0, 0.5));
  //AddSequential(new DriveTurnToAngle(145.0,5.0,0.3,-0.35));  
  //AddSequential(new DriveStraightDistance(20.0, 1.0, 0.5));
  //AddSequential(new DriveGoToTarget(0.35));


}
