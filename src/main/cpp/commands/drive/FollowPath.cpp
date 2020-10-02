/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "commands/Drive/FollowPath.h"
#include "Robot.h"
#include <math.h>
#include "RobotMap.h"
#include "frc/trajectory/TrajectoryUtil.h"

// the following only required for loading path from pathweaver file
//#include <frc/Filesystem.h>
//#include <frc/trajectory/TrajectoryUtil.h>
//#include <wpi/Path.h>
//#include <wpi/SmallString.h>

// follow path command constructor
FollowPath::FollowPath(CTrajectoryConstants::TrajectoryList nTrajectory, bool reverse) {
  // follow path requires both main drive and odometry subsystems
  AddRequirements (&Robot::m_MainDrive);
  AddRequirements (&Robot::m_Odometry);

  PathFollowCommand=NULL;
  controller = NULL;
  LeftPIDController = NULL;
  RightPIDController = NULL;

  reverse = m_reverse;

  // record name of the trajectory we are to follow
  m_TrajectoryName = nTrajectory;
}

// Called just before this Command runs the first time
void FollowPath::Initialize() {
  
  // create drive kinematics objects
  // note: voltage constraints not used at moment
  DifferentialDriveKinematics kDriveKinematics (kTrackWidth);
  SimpleMotorFeedforward <units::meters> kMotorFeedForward (ks, kv, ka);
  // DifferentialDriveVoltageConstraint autoVoltageConstraint (kMotorFeedForward, kDriveKinematics, 2_V);

  TrajectoryConfig pathconfig (kMaxSpeed, kMaxAcceleration);
  pathconfig.SetKinematics(kDriveKinematics);
  //x.AddConstraint(autoVoltageConstraint);
  //pathconfig.SetReversed(m_reverse);
 
  // load trajectory from path weaver file. Following code not fully tested
  // wpi::SmallString<64> deployDirectory;
  // frc::filesystem::GetDeployDirectory(deployDirectory);
  // wpi::sys::path::append(deployDirectory, "paths");
  // wpi::sys::path::append(deployDirectory, "GoLeft.wpilib.json");
  // trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory);

  CTrajectoryConstants TrajectoriesList;
  TrajectoriesList.SelectTrajectory(m_TrajectoryName);

  // generate trajectory to follow, given waypoints and trajectory configuration
  trajectory = TrajectoryGenerator::GenerateTrajectory(
       TrajectoriesList.GetSelectedTrajectoryStartPoint(),
        TrajectoriesList.GetSelectedTrajectory(),
        TrajectoriesList.GetSelectedTrajectoryEndPoint(),
        pathconfig);    

  // translate/rotate path so it starts the robot's current position/angle
  Translation2d translate2 = Robot::m_Odometry.GetPose2d().Translation() - (trajectory.InitialPose().Translation());
  Transform2d transform (translate2, Rotation2d(0_deg));
    trajectorynew = trajectory.TransformBy(transform);

  // set up ramsete and left/right controllers
  controller = new RamseteController (kRamseteB, kRamseteZeta);
  LeftPIDController = new frc2::PIDController (kPDriveVel, 0, 0);
  RightPIDController = new frc2::PIDController (kPDriveVel, 0, 0);
   
  // set up ramsete command to follow path
  PathFollowCommand = new frc2::RamseteCommand (
      trajectorynew,
      [this]() { return Robot::m_Odometry.GetPose2d(); },
      *controller,
      kMotorFeedForward,
      kDriveKinematics,
      [this] { return Robot::m_MainDrive.GetWheelSpeeds(); },
      *LeftPIDController,
      *RightPIDController,
      [this](auto left, auto right) { Robot::m_MainDrive.SetTankDriveVolts(-left, right); },
      {&Robot::m_MainDrive});

  // initialize command ready to run 
  PathFollowCommand->Initialize();
}

// Called repeatedly when this Command is scheduled to run
void FollowPath::Execute() {

  // execute ramsete control - ensure ramsete controller object exists to prevent fault
  if (PathFollowCommand!=NULL)
    PathFollowCommand->Execute();
}

// returns true if command is finished
bool FollowPath::IsFinished() {
    
  // this command is finished when the ramsete command is finished
  // if no ramsete command exists, then finish this command
  if (PathFollowCommand!=NULL)
    return PathFollowCommand->IsFinished();
  else 
    return true;
}


// Called once after isFinished returns true
void FollowPath::End(bool interrupted) {
  
  // call ramsete to end its command
  if (PathFollowCommand!=NULL)
    PathFollowCommand->End(false);

  delete PathFollowCommand;   PathFollowCommand=NULL;
  delete controller;          controller = NULL;
  delete LeftPIDController;   LeftPIDController = NULL;
  delete RightPIDController;  RightPIDController = NULL;
}

