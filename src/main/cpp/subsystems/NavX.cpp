/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "subsystems/NavX.h"
#include "RobotMap.h"

// constructor - used to initialize specific hardware
NavX::NavX(){

    // create navX object and set to use SPI port
    ahrs = new AHRS(SPI::Port::kMXP);

    // rest the gyro
    ahrs->Reset();

    // zero the yaw
    ZeroYaw();
}

// zero the yaw
void NavX::ZeroYaw(void){
    //zero the gyro
    ahrs->ZeroYaw();
}

// get current yaw
// returns the current yaw value (in degrees, from -180 to 180) reported by the sensor.
float NavX::GetYaw(void){
    return (ahrs->GetYaw());
}

// returns the current roll value (in degrees, from -180 to 180) reported by the sensor.
float NavX::GetRoll(void){
    return (ahrs->GetRoll());
}

// Returns the current pitch value (in degrees, from -180 to 180) reported by the sensor. Pitch is a measure of rotation around the X Axis.
float NavX::GetPitch(void){
    return (ahrs->GetPitch());
}

float NavX::GetAccelX(void){
    return (ahrs->GetRawAccelX());
}

float NavX::GetAccelY(void){
    return (ahrs->GetRawAccelY());
}
 

// ------------- Shuffleboard Functions -------------

void NavX::InitializeShuffleBoard(void)
{
    // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("NavX");
    
    ShuffleboardLayout *l1 = &Tab->GetLayout("Roll Rates", BuiltInLayouts::kList);
    l1->WithPosition(0,0);
    l1->WithSize(1,2);
    Yaw = l1->Add("Yaw", 0.0).GetEntry();
    Pitch = l1->Add("Pitch", 0.0).GetEntry();
    Roll = l1->Add("Roll", 0.0).GetEntry();

    ShuffleboardLayout *l2 = &Tab->GetLayout("Accelerometer", BuiltInLayouts::kList);
    l2->WithPosition(1,0);
    l2->WithSize(1,2);
    AccelX = l2->Add("X", 0.0).GetEntry();
    AccelY = l2->Add("Y", 0.0).GetEntry();
}

// update shuffle board with current values
void NavX::UpdateShuffleBoard(void)
{
    Yaw.SetDouble(GetYaw());
    Pitch.SetDouble(GetPitch());
    Roll.SetDouble(GetRoll());

    AccelX.SetDouble(GetAccelX());
    AccelY.SetDouble(GetAccelY());
}
