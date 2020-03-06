/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/* DELETE THE ZERO YAW BEFORE THE COMP*/
/* DELETE THE ZERO YAW BEFORE THE COMP*/
/* DELETE THE ZERO YAW BEFORE THE COMP*/
/* DELETE THE ZERO YAW BEFORE THE COMP*/

#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

// robot operator interfaces
DashboardOI Robot::m_DashboardOI;
MechanismOI Robot::m_MechanismOI;
DriverOI Robot::m_DriverOI;

// robot subsystems
#ifdef DRIVE2020
  MainDrive Robot::m_MainDrive;
#endif
#ifdef DRIVE2019
  MainDrive2019 Robot::m_MainDrive;
#endif
NavX Robot::m_NavX;
Limelight Robot::m_Limelight;
CameraTilt Robot::m_CameraTilt;
Odometry Robot::m_Odometry;
PowerPanel Robot::m_PowerPanel;
Climb Robot::m_Climb;
Shooter Robot::m_Shooter;
LED Robot::m_LED;
Intake Robot::m_Intake;
IntakeTilt Robot::m_IntakeTilt;
Uplifter Robot::m_Uplifter;
Winch Robot::m_Winch;
// UltrasonicSensor Robot::m_UltrasonicSensor;
// RangeFinder Robot::m_RangeFinder;
// WoF Robot::m_WoF;


// commands
ChangeLED Robot::m_ChangeLED;
AutoComplex Robot::m_AutoComplex;
AutoSimple Robot::m_AutoSimple;


// ------------------------ General (All Modes) --------------------


void Robot::RobotInit() {

// create default teleop command
m_defaultTeloOpCommand = new Tank();

// initialize dashboard
m_DashboardOI.InitializeDashBoard();

// initially robot subsystems are not initialized
m_IsRobotInitialized=false;

// zero robot yaw
    m_NavX.ZeroYaw();

}

 // This function is called every robot packet, no matter the mode. Use
 // this for items like diagnostics that you want to run during disabled,
 // autonomous, teleoperated and test.
 // <p> This runs after the mode specific periodic functions, but before
 // LiveWindow and SmartDashboard integrated updating.
void Robot::RobotPeriodic() {
  // ask scheduler to run and do its job
  frc2::CommandScheduler::GetInstance().Run();

  // update driver dashboard
  m_DashboardOI.UpdateDashBoard();
}


// ------------------------ Disabled Mode --------------------


// This function is called once each time the robot enters Disabled mode. You
// can use it to reset any subsystem information you want to clear when the
// robot is disabled.
void Robot::DisabledInit() {

  // turn off LEDs
  m_LED.SetLEDsOff();
}

void Robot::DisabledPeriodic() {}

// ------------------------ Autonomous Mode --------------------



// This autonomous runs the autonomous command selected by your {@link
// RobotContainer} class.
void Robot::AutonomousInit() {
  //m_autonomousCommand = m_container.GetAutonomousCommand();
  //
  //if (m_autonomousCommand != nullptr) {
  //  m_autonomousCommand->Schedule();
  //}

  // has robot been initialized yet?
  if (!m_IsRobotInitialized)
  {
    // zero robot yaw
    m_NavX.ZeroYaw();

    //initialize odometry
    m_Odometry.Initialize();
    
    // set camera pipeline to chevron
    m_Limelight.SetPipeline(0);
    //m_CameraTilt.SetTiltPos(0);
    
    // robot subsystems are now initialized
    m_IsRobotInitialized = true;
  }

  // set intake tilt target position to its current position, so it does not 'snap' into place
  Robot::m_IntakeTilt.SetIntakeTiltTargetAnalog(Robot::m_IntakeTilt.GetEncoderPosition());

   m_ChangeLED.Schedule(); 

   // get idle speed from shuffleboard and set shooter speed
   Robot::m_Shooter.SetSpeed(Robot::m_Shooter.GetIdleSpeedSliderValue());


   if (m_DashboardOI.GetAutoCommandState1())
     m_AutoSimple.Schedule();
      
}

void Robot::AutonomousPeriodic() {
  //update robot odometry
  m_Odometry.Update();
}


// ------------------------ Teleop Mode --------------------


void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  //if (m_autonomousCommand != nullptr) {
  //  m_autonomousCommand->Cancel();
  //  m_autonomousCommand = nullptr;
  //}

  // set defualt command for teleop operation - i.e tank mode
  m_MainDrive.SetDefaultCommand(*m_defaultTeloOpCommand);

  // has robot been initialized yet?
  if (!m_IsRobotInitialized)
  {
    // zero robot yaw
    m_NavX.ZeroYaw();
    
    // set camera pipeline to chevron
    m_Limelight.SetPipeline(0);
    // m_CameraTilt.SetTiltPos(0);

    //initialize odometry
    m_Odometry.Initialize();
    
    // robot subsystems are now initialized
    m_IsRobotInitialized = true;
  }

  // set intake tilt target position to its current position, so it does not 'snap' into place
  Robot::m_IntakeTilt.SetIntakeTiltTargetAnalog(Robot::m_IntakeTilt.GetEncoderPosition());

  //YOU MUST DELETE THIS BEFORE A COMPETITION. I REPEAT: YOU MUST DELETE
  m_NavX.ZeroYaw();

  m_ChangeLED.Schedule();
  
  // get idle speed from shuffleboard and set shooter speed
  Robot::m_Shooter.SetSpeed(Robot::m_Shooter.GetIdleSpeedSliderValue());

}


// This function is called periodically during operator control.
void Robot::TeleopPeriodic() {

  m_Odometry.Update();
}


// ------------------------ Test Mode --------------------


// This function is called periodically during test mode.
void Robot::TestPeriodic() {}


// ------------------------ Main Program --------------------

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
