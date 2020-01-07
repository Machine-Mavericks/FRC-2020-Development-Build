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

    // default angle
    SetTilt(CAMERA_TILTANGLE_BALL);
}

// default command to run with the subsystem
void CameraTilt::InitDefaultCommand()
{
}

// sets camera tilt to desired angle
// Value is angle (deg)
void CameraTilt::SetTilt(float value)
{
    // set tilt value
    m_Servo->SetAngle(value);
}

