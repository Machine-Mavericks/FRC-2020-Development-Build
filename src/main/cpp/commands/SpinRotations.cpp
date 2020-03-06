/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "subsystems/WoF.h"
#include "commands/SpinRotations.h"


SpinRotations::SpinRotations(int rotations) {
    //add requirements
    //AddRequirements (&Robot::m_WoF);
}

// Called once when the command executes
void SpinRotations::Initialize() {
    //int m_initColor = Robot::m_WoF.GetColor();
    //int m_counter = 0;
    //int m_currentColor = 0;

}

void SpinRotations::Execute(){
    //if (m_initColor != Robot::m_WoF.GetColor()){
    //    m_initColor = m_currentColor;
    //    m_counter += 1;
    //}
}

bool SpinRotations::IsFinished(){
    //return m_counter == m_rotations;
    return true;
}

void SpinRotations::End(bool interrupted){}