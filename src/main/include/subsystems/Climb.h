/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc/DoubleSolenoid.h"
#include <frc/Shuffleboard/Shuffleboard.h>

using namespace frc;

class Climb : public frc::Subsystem {
 private:
    // It's desirable that everything possible under private except
    // for methods that implement subsystem capabilities
    DoubleSolenoid *front_DoubleSolenoid;
    DoubleSolenoid *rear_DoubleSolenoid;

   // shuffleboard controls
   nt::NetworkTableEntry FrontCylindersDown, BackCylindersDown;

 public:
  Climb();
  void InitDefaultCommand() override;

  // ------------- Climb Functions -------------

  // These are functions we added ourselves that provide useful(and simplified) control of the Climb

  // Function to command Climb pistons to move to a fixed position
  void SetClimbFrontTargetPosition(int pos);
  void SetClimbRearTargetPosition(int pos);

  // Function to return Climb pistons position
  int GetClimbFrontTargetPosition(void);
  int GetClimbRearTargetPosition(void); 


  // ------------- Shuffleboard Functions -------------

  // update shuffle board with current target values
  void InitializeShuffleBoard(void);

  // update shuffle board with current target values
  void UpdateShuffleBoard(void);

};
                  