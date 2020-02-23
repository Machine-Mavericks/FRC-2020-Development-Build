/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "subsystems/WoF.h"
#include "commands/ChangeLED.h"
#include "subsystems/LED.h"
#include "subsystems/Limelight.h"


ChangeLED::ChangeLED() {
    //add requirements
    AddRequirements (&Robot::m_LED);
    //AddRequirements (&Robot::m_Limelight);
}

// Called once when the command executes
void ChangeLED::Initialize() {
    Robot::m_LED.SetRGB(0, 255, 0);
    counter = 0;
    LEDON = false;
}

void ChangeLED::Execute(){
    
    if (counter>=10)
        counter = 0;

    if (counter >=8)
        LEDON = true;
    else
        LEDON = false;

    if (LEDON &&
        Robot::m_Limelight.GetTargetEstimation().Detected && 
        fabs(Robot::m_Limelight.GetTargetEstimation().XAngle) < 1.0)
        Robot::m_LED.SetRGB(0, 255, 0);
    else
        Robot::m_LED.SetRGB(0, 0, 0);
    
    counter += 1;
}

bool ChangeLED::IsFinished(){
    return false;
}

void ChangeLED::End(bool interrupted){}