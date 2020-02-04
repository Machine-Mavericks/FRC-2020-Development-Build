/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

// robot preferences definitions
#include "RobotPrefs.h"

// operator interface definitions
#include "DriverOI.h"
#include "MechanismOI.h"
#include "DashboardOI.h"

// subsystem definitions
#include "subsystems/MainDrive.h"
#include "subsystems/NavX.h"
#include "subsystems/Limelight.h"
#include "subsystems/CameraTilt.h"
#include "subsystems/ColorSensor.h"


// command definitions
#include "commands/MyAutoCommand.h"



class Robot : public frc::TimedRobot {
  public:
  // create preferences
  static RobotPrefs m_Prefs;

  // create commands
  static MyAutoCommand m_MyAutoCommand;
 
  // create subsystems;
<<<<<<< Updated upstream
  static MainDrive m_MainDrive;
  static NavX m_NavX;
=======
  #ifdef DRIVE2019
    static MainDrive2019 m_MainDrive;
  #endif
  #ifdef DRIVE2020
    static MainDrive m_MainDrive;
  #endif
>>>>>>> Stashed changes
  static Limelight m_Limelight;
  static CameraTilt m_CameraTilt;
  static ColorSensor m_ColorSensor;
 
  
  // create robot driver interfaces
  static DriverOI m_DriverOI;
  static MechanismOI m_MechanismOI;
  static DashboardOI m_DashboardOI;

  // Robot mode-independent funtcions
  void RobotInit() override;
  void RobotPeriodic() override;
  
  // Robot Disabled mode related functions
  void DisabledInit() override;
  void DisabledPeriodic() override;
 
  // Robot Autonomous mode related functions
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  
  // Robot TeleOp mode related functions
  void TeleopInit() override;
  void TeleopPeriodic() override;
  
  // Robot Test mode related functions
  void TestPeriodic() override;

  private:
  
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc::Command* m_autonomousCommand = nullptr;
  MyAutoCommand m_myAuto;
  frc::SendableChooser<frc::Command*> m_chooser;
};
