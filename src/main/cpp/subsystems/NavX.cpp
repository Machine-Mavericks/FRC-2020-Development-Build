/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "subsystems/NavX.h"
#include "RobotMap.h"

// constructor - used to initialize specific hardware
NavX::NavX() : Subsystem("Navx") {

    // create navX object and set to use SPI port
    ahrs = new AHRS(SPI::Port::kMXP);

    // rest the gyro
    ahrs->Reset();

    // zero the yaw
    ZeroYaw();
}

// default command to run with the subsystem
void NavX::InitDefaultCommand() {
  // For drive there is no default command
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
 

