/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "frc/trajectory/Trajectory.h"
#include "frc/trajectory/TrajectoryGenerator.h"
#include "frc2/command/RamseteCommand.h"
#include "frc/PIDController.h"
#include "TrajectoryConstants.h"

 
using namespace frc;


class FollowPath : public frc2::CommandHelper<frc2::CommandBase, FollowPath> {
 public:
  
  // Constructor - Run once when command is created
  FollowPath(CTrajectoryConstants::TrajectoryList nTrajectory, bool reverse);

  // Called just before this Command runs the first time
  void Initialize() override;
  
  // Called repeatedly when this Command is scheduled to run
  void Execute() override;

  // returns true if command is finished
  bool IsFinished() override;

  // Called once after isFinished returns true
  void End(bool interrupted) override;


  private:

  //set trajectory to follow
  CTrajectoryConstants::TrajectoryList m_TrajectoryName;

  // set maximum robot speed(m/s) and acceleration (m/s2) for path
  static constexpr auto  kMaxSpeed = 2.5_mps;
  static constexpr auto  kMaxAcceleration = 2_mps_sq;

  bool m_reverse;

  // define robot feedforward constants
  static constexpr auto ks = 0.22_V;
  static constexpr auto kv = 1.75 * 1_V * 1_s / 1_m;             // =3.2 for 2020 robot
  static constexpr auto ka = 0.1 * 1_V * 1_s * 1_s / 1_m;        // =0 for 2020 robot
  
  // robot track width distance (beween center of wheels)
  static constexpr auto kTrackWidth = 0.535_m;

  // ramsete constants
  static constexpr float kRamseteB = 2.0;         // = 2.0 for 2020 robot
  static constexpr float kRamseteZeta = 0.8;      // = 0.7 for 2020 robot

  // Left and Right PD controller gains
  static constexpr float kPDriveVel = 1.0;
  static constexpr float kDDriveVel = 0.0;

  // the trajectory we are to follow
  Trajectory trajectory, trajectorynew;

  // command to follow trajectory
  frc2::RamseteCommand *PathFollowCommand;

  // create ramsetecontroller for command to use
  RamseteController *controller;
  frc2::PIDController *LeftPIDController;
  frc2::PIDController *RightPIDController;
    

};
