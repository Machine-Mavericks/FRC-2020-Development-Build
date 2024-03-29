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
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <units/units.h>

using namespace frc;

class Odometry : public frc2::SubsystemBase {
 public:

   // constructor - used to initialize specific hardware
   Odometry();

   // initialize robot odometry based - use shuffleboard settings and current gyro angle
   void Initialize();

   // used to set or reset odometry
   // function assumes robot and gyro angle are the same
   // x, y displacement in m
   // angle in deg
   void SetPosition(float x, float y, float angle);


   // update current robot odometry  - call frm robot.c @ 50Hz
   void Update();
  
   // return current odometry x displacement (in m)
   float GetX();

   // return current odometry y displacement (in m)
   float GetY();

   // return current odometry angle (in deg)
   float GetAngle();


   // ------------- Functions Required by Tractory Control -------------

   // return robot's current position vector Pose2d
   Pose2d GetPose2d();


   // ------------- Shuffleboard Functions -------------

   void InitializeShuffleBoard(void);
   void UpdateShuffleBoard(void);


 private:

    //make odometry pointer
    DifferentialDriveOdometry *m_Odometry;

   // Shubbleboard Controls
   nt::NetworkTableEntry RobotX, RobotY, RobotAngle;
   nt::NetworkTableEntry InitialX, InitialY;

};
