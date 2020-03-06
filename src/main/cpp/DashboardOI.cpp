/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// #include <frc/WPILib.h>
#include "DashboardOI.h"
#include "Robot.h"
#include <frc/Shuffleboard/Shuffleboard.h>
#include "frc/shuffleboard/WidgetType.h"

// class constructor - executed upon creation of DashboardOI object
DashboardOI::DashboardOI() { }

// initialize dashboard
void DashboardOI::InitializeDashBoard(void)
{
   // add autonomous commands to shuffleboard
    InitializeCommandsPage();
    
    // initialize shuffleboard subsystem pages
    Robot::m_MainDrive.InitializeShuffleBoard();
    Robot::m_NavX.InitializeShuffleBoard();
    Robot::m_Limelight.InitializeShuffleBoard();
    Robot::m_Odometry.InitializeShuffleBoard();
    Robot::m_PowerPanel.InitializeShuffleBoard();
    Robot::m_Shooter.InitializeShuffleboard();
    Robot::m_Intake.InitializeShuffleboard();
    Robot::m_IntakeTilt.InitializeShuffleboard();
    Robot::m_Uplifter.InitializeShuffleboard();
    Robot::m_Climb.InitializeShuffleboard();
    Robot::m_Winch.InitializeShuffleboard();
    // Robot::m_UltrasonicSensor.InitializeShuffleBoard();
    // Robot::m_RangeFinder.InitializeShuffleBoard();
}

// Update dashboard
void DashboardOI::UpdateDashBoard(void)
{   
    // update subsystem values to Shuffleboard
    Robot::m_MainDrive.UpdateShuffleBoard();
    Robot::m_NavX.UpdateShuffleBoard();
    Robot::m_Limelight.UpdateShuffleBoard();
    Robot::m_Odometry.UpdateShuffleBoard();
    Robot::m_PowerPanel.UpdateShuffleBoard();
    Robot::m_Shooter.UpdateShuffleboard();
    Robot::m_Intake.UpdateShuffleboard();
    Robot::m_IntakeTilt.UpdateShuffleboard();
    Robot::m_Uplifter.UpdateShuffleboard();
    Robot::m_Climb.UpdateShuffleboard();
    Robot::m_Winch.UpdateShuffleboard();
    // Robot::m_UltrasonicSensor.UpdateShuffleBoard();
    // Robot::m_RangeFinder.UpdateShuffleBoard();
 }


void DashboardOI::InitializeCommandsPage(void)
{
  // Main Tab
  ShuffleboardTab *Tab = &Shuffleboard::GetTab("Auto Cmds");

  // add autonomous commands to page    
  AutoCommand1 = Tab->AddPersistent("Auto 1", false). WithWidget(BuiltInWidgets::kToggleSwitch).WithPosition(0,0).WithSize(1,1).GetEntry();
  AutoCommand2 = Tab->AddPersistent("Auto 2", false). WithWidget(BuiltInWidgets::kToggleSwitch).WithPosition(2,0).WithSize(1,1).GetEntry();
  AutoCommand3 = Tab->AddPersistent("Auto 3", false). WithWidget(BuiltInWidgets::kToggleSwitch).WithPosition(4,0).WithSize(1,1).GetEntry();
}

// returns position of throttle control on shuffleboard - if not available, returns 1.0
bool DashboardOI::GetAutoCommandState1(void) { return AutoCommand1.GetBoolean(false); }
bool DashboardOI::GetAutoCommandState2(void) { return AutoCommand2.GetBoolean(false); }
bool DashboardOI::GetAutoCommandState3(void) { return AutoCommand3.GetBoolean(false); }