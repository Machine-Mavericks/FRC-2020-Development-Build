/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climb.h"
#include "RobotMap.h"

Climb::Climb() : Subsystem("Climb") {
    // define solenoid object - set channel numbers for open/close
   front_DoubleSolenoid = new DoubleSolenoid(FRONT_PISTON_EXTEND_CHANNEL,FRONT_PISTON_RETRACT_CHANNEL);
   rear_DoubleSolenoid = new DoubleSolenoid(REAR_PISTON_EXTEND_CHANNEL,REAR_PISTON_RETRACT_CHANNEL);

   // set initial solenoid position (retracted)
   SetClimbFrontTargetPosition(0);
   SetClimbRearTargetPosition(0);
}


void Climb::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

// ------------- Climb Functions -------------

void Climb::SetClimbFrontTargetPosition(int pos){
    // depending on desired position, turn on forward or reverse valve
    switch (pos)
    {
        case 1:
            front_DoubleSolenoid->Set(DoubleSolenoid::kForward);
            break;
        case 0:
            front_DoubleSolenoid->Set(DoubleSolenoid::kReverse);
            break;
        case -1:
            front_DoubleSolenoid->Set(DoubleSolenoid::kOff);
            break;
    }
}

void Climb::SetClimbRearTargetPosition(int pos){
    // depending on desired position, turn on forward or reverse valve
    switch (pos)
    {
        case 1:
            rear_DoubleSolenoid->Set(DoubleSolenoid::kForward);
            break;
        case 0:
            rear_DoubleSolenoid->Set(DoubleSolenoid::kReverse);
            break;
        case -1:
            rear_DoubleSolenoid->Set(DoubleSolenoid::kOff);
            break;
    }
}



// Function to return Climb position
// Output: 1 if open, 0 if closed, -1 if off (or otherwise) 
int Climb::GetClimbFrontTargetPosition(void){
   int pos = -1;
    if (front_DoubleSolenoid->Get() == DoubleSolenoid::kForward)
        pos = 1;
    if (front_DoubleSolenoid->Get() == DoubleSolenoid::kReverse)
        pos = 0;
    if (front_DoubleSolenoid->Get() == DoubleSolenoid::kOff)
        pos = -1;
    return pos;
}

// Function to return Climb position
// Output: 1 if open, 0 if closed, -1 if off (or otherwise) 
int Climb::GetClimbRearTargetPosition(void){
   int pos = -1;
    if (rear_DoubleSolenoid->Get() == DoubleSolenoid::kForward)
        pos = 1;
    if (rear_DoubleSolenoid->Get() == DoubleSolenoid::kReverse)
        pos = 0;
    if (rear_DoubleSolenoid->Get() == DoubleSolenoid::kOff)
        pos = -1;
    return pos;
}

// ------------- Shuffleboard Functions -------------

// update shuffle board with current target values
void Climb::InitializeShuffleBoard(void)
{
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Climb");

    FrontCylindersDown = Tab->Add("F Cyl Down", false).GetEntry();
    BackCylindersDown = Tab->Add("R Cyl Down", false).GetEntry();
}

// update shuffle board with current target values
void Climb::UpdateShuffleBoard(void)
{
    FrontCylindersDown.SetBoolean(GetClimbFrontTargetPosition()==1);
    BackCylindersDown.SetBoolean(GetClimbRearTargetPosition()==1);
}
