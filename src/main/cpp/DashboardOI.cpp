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
    // initialize shuffleboard
    Robot::m_MainDrive.InitializeShuffleBoard();
    Robot::m_NavX.InitializeShuffleBoard();
    Robot::m_Limelight.InitializeShuffleBoard();
    Robot::m_UltrasonicSensor.InitializeShuffleBoard();
    Robot::m_Odometry.InitializeShuffleBoard();
    Robot::m_PowerPanel.InitializeShuffleBoard();
    Robot::m_Shooter.InitializeShuffleboard();
    Robot::m_RangeFinder.InitializeShuffleBoard();
    Robot::m_Intake.InitializeShuffleboard();
    Robot::m_IntakeTilt.InitializeShuffleboard();
    Robot::m_Uplifter.InitializeShuffleboard();
}

// Update dashboard
void DashboardOI::UpdateDashBoard(void)
{   
    // update subsystem values to Shuffleboard
    Robot::m_MainDrive.UpdateShuffleBoard();
    Robot::m_NavX.UpdateShuffleBoard();
    Robot::m_Limelight.UpdateShuffleBoard();
    Robot::m_UltrasonicSensor.UpdateShuffleBoard();
    Robot::m_Odometry.UpdateShuffleBoard();
    Robot::m_PowerPanel.UpdateShuffleBoard();
    Robot::m_Shooter.UpdateShuffleboard();
    Robot::m_RangeFinder.UpdateShuffleBoard();
    Robot::m_Intake.UpdateShuffleboard();
    Robot::m_IntakeTilt.UpdateShuffleboard();
    Robot::m_Uplifter.UpdateShuffleboard();
 }
