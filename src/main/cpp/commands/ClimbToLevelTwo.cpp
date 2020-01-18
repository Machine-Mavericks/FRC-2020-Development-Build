/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbToLevelTwo.h"
#include "commands/TiltUp.h"
#include "commands/ElevatorGoToEncoder.h"
#include "commands/TimeDelay.h"
#include "commands/DriveStraightDistance.h"
#include "commands/DriveStraightTilStopped.h"
#include "commands/Level2.h"


ClimbToLevelTwo::ClimbToLevelTwo() {
  // lower wrist and drive forward to human player station
  AddSequential(new TiltUp());
  AddSequential(new ElevatorGoToEncoder(0));
 
  AddSequential(new Level2(FRONTPISTON,EXTENDED));
  AddSequential(new TimeDelay(1.0));
  AddSequential(new DriveStraightTilStopped(50.0,0.5));
  
  AddSequential(new Level2(BACKPISTON,EXTENDED));
  //AddSequential(new TimeDelay(1.0));
  

  AddSequential(new Level2(FRONTPISTON,RETRACTED));
  AddSequential(new TimeDelay(1.0));
    
  AddSequential(new DriveStraightTilStopped(50.0,0.5));
  AddSequential(new Level2(BACKPISTON,RETRACTED));

  AddSequential(new TimeDelay(1.0));

  AddSequential(new DriveStraightTilStopped(12.0,0.2));

  AddSequential(new TimeDelay(100.0));

}