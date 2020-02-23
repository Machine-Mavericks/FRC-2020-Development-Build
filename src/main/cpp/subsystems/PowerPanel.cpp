/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/PowerPanel.h"
#include "Robot.h"

// power panel constructor
PowerPanel::PowerPanel() {  

  // create power distribution panel object
  m_PowerPanel = new PowerDistributionPanel(0);

  // reset energy to zero
  m_PowerPanel->ResetTotalEnergy();
}


// ------------- Shuffleboard Functions -------------


// initialize shuffleboard controls
void PowerPanel::InitializeShuffleBoard(void)
{
    // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("PowerPanel");
    
    ShuffleboardLayout *l1 = &Tab->GetLayout("Instantaneous", BuiltInLayouts::kList);
    l1->WithPosition(0,0);
    l1->WithSize(1,2);
    Voltage = l1->Add("Volts(V)", 0.0).GetEntry();
    TotalCurrent = l1->Add("Current(A)", 0.0).GetEntry();
    
    ShuffleboardLayout *l2 = &Tab->GetLayout("Totals", BuiltInLayouts::kList);
    l2->WithPosition(2,0);
    l2->WithSize(1,2);
    TotalPower= l2->Add("Power(W)", 0.0).GetEntry();
    TotalEnergy= l2->Add("Energy(J)", 0.0).GetEntry();
}

// update shuffle board with current values
void PowerPanel::UpdateShuffleBoard(void)
{
    Voltage.SetDouble(m_PowerPanel->GetVoltage());
    TotalCurrent.SetDouble(m_PowerPanel->GetTotalCurrent()); 
    TotalPower.SetDouble(m_PowerPanel->GetTotalPower());
    TotalEnergy.SetDouble(m_PowerPanel->GetTotalEnergy()); 
}
