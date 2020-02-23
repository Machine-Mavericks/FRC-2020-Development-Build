/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "RobotMap.h"
#include <frc/Shuffleboard/Shuffleboard.h>
#include "frc/PowerDistributionPanel.h"

using namespace frc;

class PowerPanel: public frc2::SubsystemBase {
 public:

   // constructor - used to initialize specific hardware
   PowerPanel();


   // ------------- Shuffleboard Functions -------------
   
   void InitializeShuffleBoard(void);
   void UpdateShuffleBoard(void);

 private:

   // power distribution panel
  PowerDistributionPanel *m_PowerPanel;

   // Shubbleboard Controls
   nt::NetworkTableEntry Voltage, TotalCurrent, TotalPower, TotalEnergy;

};
