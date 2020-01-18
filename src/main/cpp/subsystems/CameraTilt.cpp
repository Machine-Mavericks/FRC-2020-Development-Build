/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraTilt.h"
#include "RobotMap.h"


CameraTilt::CameraTilt() : Subsystem("CameraTilt")
{
    // create PWM object on RoboRIO
    m_Servo = new Servo(CAMERA_SERVO_ID);

    // default angle for chevron
    SetTiltPos(0);
}

// default command to run with the subsystem
void CameraTilt::InitDefaultCommand()
{
}

// sets camera tilt to desired angle
// == 0 for chevron
// == 1 for ball
void CameraTilt::SetTiltPos(unsigned int Pos)
{
    if (Pos == 0)
        m_Servo->SetAngle(CAMERA_TILTANGLE_CHEVRON + ChevronAdjust.GetDouble(0.0));
    
    else if (Pos == 1)
        m_Servo->SetAngle(CAMERA_TILTANGLE_BALL + BallAdjust.GetDouble(0.0));
}

// ------------- Shuffleboard Functions -------------

void CameraTilt::InitializeShuffleBoard(void)
{
    // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Camera Tilt");

    ShuffleboardLayout *l1 = &Tab->GetLayout("Positions", BuiltInLayouts::kList);
    l1->WithPosition(1,0);
    l1->WithSize(1,2);
    l1->Add("Ball", CAMERA_TILTANGLE_BALL);
    l1->Add("Chevron", CAMERA_TILTANGLE_CHEVRON);
    
    ShuffleboardLayout *l2 = &Tab->GetLayout("Adjusts", BuiltInLayouts::kList);
    l2->WithPosition(2,0);
    l2->WithSize(1,2);
    BallAdjust=l2->AddPersistent("Ball", 0.0).GetEntry();
    ChevronAdjust=l2->AddPersistent("Chevon", 0.0).GetEntry();
}

// update shuffle board with current drive values
void CameraTilt::UpdateShuffleBoard(void) {

  
}
