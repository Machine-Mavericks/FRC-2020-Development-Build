/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "subsystems/WoF.h"
#include "commands/GoToColor.h"


GoToColor::GoToColor(int color) {
    //add requirements
    AddRequirements (&Robot::m_WoF);
}

// Called once when the command executes
void GoToColor::Initialize() {
    int m_initColor = Robot::m_WoF.GetColor();

}

void GoToColor::Execute(){
}

bool GoToColor::IsFinished(){}

void GoToColor::End(bool interrupted){}