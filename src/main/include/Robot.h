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
#include "subsystems/Elevator.h"
#include "subsystems/Limelight.h"
#include "subsystems/CameraTilt.h"
#include "subsystems/IntakeTilt.h"
#include "subsystems/Claw.h"
#include "subsystems/Snowblower.h"
#include "subsystems/IndicatorLight.h"
#include "subsystems/AirCompressor.h"
#include "subsystems/Climb.h"


// command definitions
#include "commands/MyAutoCommand.h"
#include "commands/TiltHome.h"
#include "commands/ClawHome.h"
#include "commands/ChangeLight.h"



class Robot : public frc::TimedRobot {
  public:
  // create preferences
  static RobotPrefs m_Prefs;

  // create commands
  static TiltHome m_TiltHome;
  static ClawHome m_ClawHome;
  static ChangeLight m_ChangeLight;
 
  // create subsystems;
  static MainDrive m_MainDrive;
  static NavX m_NavX;
  static Elevator m_Elevator;
  static Limelight m_Limelight;
  static CameraTilt m_CameraTilt;
  static IntakeTilt m_IntakeTilt;
  static Claw m_Claw;
  static Snowblower m_Snowblower;
  static AirCompressor m_AirCompressor;
  static Climb m_Climb;
  static IndicatorLight m_IndicatorLight;
 
  
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
  
  // Flag to indicate if robot subsystems initialized
  // used to prevent re-initializing subsystems when robot switches from autotonomous to teleop modes
  static bool m_IsRobotInitialized;

  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc::Command* m_autonomousCommand = nullptr;
  MyAutoCommand m_myAuto;
  frc::SendableChooser<frc::Command*> m_chooser;

};
