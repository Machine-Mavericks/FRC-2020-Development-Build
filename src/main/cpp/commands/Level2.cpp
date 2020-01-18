/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Level2.h"
#include "subsystems/climb.h"
#include "robot.h"

//open/close the claw
//1=open, 0=close
Level2::Level2(int piston, int pos) {
   
   // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_Climb);

  m_piston = piston; //m_piston is 1 or 2 depending on thether it's the front (0) or rear (1).
  m_pos = pos;       // m_pos is 0 or 1 depending on whether it's extended (1) or retracted (2).
}


// Called once when the command executes
void Level2::Initialize() {

  switch (m_piston)
  {
    case BACKPISTON:
      if (m_pos == EXTENDED) {
        Robot::m_Climb.SetClimbRearTargetPosition(EXTENDED);
      }
      else {
        Robot::m_Climb.SetClimbRearTargetPosition(RETRACTED);
      }   
      break;

    case FRONTPISTON:
      if (m_pos == EXTENDED) {
        Robot::m_Climb.SetClimbFrontTargetPosition(EXTENDED);
      }
      else {
        Robot::m_Climb.SetClimbFrontTargetPosition(RETRACTED);
      }   
      break;
  }
 /* 
  if(positionfront == -1) {
    //positionfront = Robot::m_Climb.GetClimbFrontTargetPosition();
    Robot::m_Climb.SetClimbRearTargetPosition(positionrear);
  }
  if(positionrear == -1) {
    //positionrear = Robot::m_Climb.GetClimbRearTargetPosition();
    Robot::m_Climb.SetClimbFrontTargetPosition(positionfront);
  }
 */ 
  
 }
