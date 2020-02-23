/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include "RobotMap.h"

//include subsystems
#include "subsystems/MainDrive2019.h"
#include "subsystems/MainDrive.h"
#include "subsystems/Limelight.h"
#include "subsystems/CameraTilt.h"
#include "subsystems/Shooter.h"
#include "subsystems/LED.h"
#include "subsystems/NavX.h"
#include "subsystems/Odometry.h"
#include "subsystems/PowerPanel.h"
#include "subsystems/UltrasonicSensor.h"
#include "subsystems/RangeFinder.h"
#include "subsystems/WoF.h"
#include "subsystems/Climb.h"
#include "subsystems/Intake.h"
#include "subsystems/Uplifter.h"


//include operator interfaces
#include "MechanismOI.h"
#include "DriverOI.h"
#include "DashboardOI.h"

// default command to run in teleop
#include "commands/drive/Tank.h"

//include commands
#include "commands/ChangeLED.h"
#include "commands/AutoComplex.h"
#include "commands/AutoSimple.h"


class Robot : public frc::TimedRobot {
  public:

  // create subsystems;
  #ifdef DRIVE2019
    static MainDrive2019 m_MainDrive;
  #endif
  #ifdef DRIVE2020
    static MainDrive m_MainDrive;
  #endif
  static Limelight m_Limelight;
  static CameraTilt m_CameraTilt;
  static NavX m_NavX;
  static Odometry m_Odometry;
  static PowerPanel m_PowerPanel;
  static UltrasonicSensor m_UltrasonicSensor;
  static RangeFinder m_RangeFinder;
  static WoF m_WoF;
  static LED m_LED;
  static Intake m_Intake;

  // create robot driver interfaces
  static DriverOI m_DriverOI;
  static MechanismOI m_MechanismOI;
  static DashboardOI m_DashboardOI;
  static Climb m_Climb;
  static Shooter m_Shooter;
  static Uplifter m_Uplifter;

  //create commands
  static ChangeLED m_ChangeLED;
  static AutoComplex m_AutoComplex;
  static AutoSimple m_AutoSimple;

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
  frc2::Command* m_autonomousCommand = nullptr;

  // default command for teleop
  Tank *m_defaultTeloOpCommand = nullptr;

  // Flag to indicate if robot subsystems initialized
  // used to prevent re-initializing subsystems when robot switches from autotonomous to teleop modes
  bool m_IsRobotInitialized;

};
