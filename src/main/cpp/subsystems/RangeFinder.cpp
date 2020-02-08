/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/RangeFinder.h"
#include "RobotMap.h"


RangeFinder::RangeFinder(){
    m_RangeFinder = new Ultrasonic(RANGEFINDER_PING_CHANNEL, RANGEFINDER_ECHO_CHANNEL, Ultrasonic::kInches);
    m_RangeFinder->SetAutomaticMode(true);
    m_RangeFinder->SetEnabled(true);

}

// Returns distance to target
double RangeFinder::GetRangeInches()
{ 
  // return motor drive current
    return m_RangeFinder->GetRangeInches();
}

double RangeFinder::GetRangeMM()
{ 
  // return motor drive current
    return m_RangeFinder->GetRangeMM();
}


// ------------- Shuffleboard Functions -------------

// update shuffle board with current target values
void RangeFinder::InitializeShuffleBoard(void)
{
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("RangeFinder");

    Range = Tab->Add("Range", 0.0).GetEntry();
 }

// update shuffle board with current target values
void RangeFinder::UpdateShuffleBoard(void)
{
    Range.SetDouble(GetRangeInches());
    //Range.SetDouble(122.35);
}
