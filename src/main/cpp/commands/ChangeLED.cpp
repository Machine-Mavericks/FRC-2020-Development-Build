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
}

// Called once when the command executes
void ChangeLED::Initialize() {
    
    // initially LEDs are off
    Robot::m_LED.SetLEDsOff();

    counter = 0;
    LEDON = false;
}

void ChangeLED::Execute(){
    
    // following code only turns LEDs on 20% of time (20% duty cycle)
    if (counter>=10)
        counter = 0;
    if (counter >=8)
        LEDON = true;
    else
        LEDON = false;
    counter += 1;
    
    // do we have a target and within 1 deg - if so, turn on blue LEDs
    if ((counter==8) &&
        Robot::m_Limelight.GetTargetEstimation().Detected && 
        fabs(Robot::m_Limelight.GetTargetEstimation().XAngle) < 1.0)
        
        Robot::m_LED.SetLEDsBlue();
    else
        // no target turn LEDs off
        Robot::m_LED.SetLEDsOff(); 
}

// this command never finishes
bool ChangeLED::IsFinished(){
    return false;
}

void ChangeLED::End(bool interrupted){

  // turn LEDs off
  Robot::m_LED.SetLEDsOff(); 

}