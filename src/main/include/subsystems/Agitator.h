/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include <frc/Shuffleboard/Shuffleboard.h>

using namespace frc;

class Agitator : public frc2::SubsystemBase {
 
 public:

  // constructor - used to initialize specific hardware
  Agitator();

  // ------------- Speed Control Functions -------------
  // SetSpeed method used to set the top and bottom speeds of the motors. This is always passed as a pair.
  void Start(void);
  //stop the motors all-together, should you ever want to do that.
  void Stop(void);


  
  private:
  
  // define drive motors
  WPI_TalonFX *m_AgitatorMotor;
};