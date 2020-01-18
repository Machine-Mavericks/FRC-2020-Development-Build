/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// RobotDrive subsystem represents the main robot drive system
// which consists of four drive motors - two for left, and two for right side

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Spark.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <ctre/Phoenix.h>
#include <frc/Encoder.h>

using namespace frc;

class MainDrive : public frc::Subsystem {
 private:

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  // define drive motors - assign each to specific PWN channel
  WPI_VictorSPX *m_MotorFrontLeft;
  WPI_VictorSPX *m_MotorRearLeft;
  WPI_VictorSPX *m_MotorFrontRight;
  WPI_VictorSPX *m_MotorRearRight;

  // create overall drive system
  DifferentialDrive *m_Drive;

  // create encoder objects
  frc::Encoder *m_EncoderRight;
  frc::Encoder *m_EncoderLeft;

public:

  // constructor - used to initialize specific hardware
  MainDrive();

  // default command to run with the subsystem
  void InitDefaultCommand() override;

  // Drive in Tank Drive - where left and right motors are driven independently
  void SetTankDrive(float LeftSpeed, float RightSpeed);

  // Drive robot in Arcade Drive (Constant arc speed around z axis)
  void SetArcadeDrive(float XSpeed, float ZRotation, bool Quickturn);

  // Drive robot in Curvature Drive (Constant rotational speed around z axis)
  void SetCurvatureDrive(float XSpeed, float ZSpeed, bool Quickturn);
 

  // ------------- Drive Encoder Functions -------------


  // reset the left /right encoders
  void ResetLeftEncoder(void);
  void ResetRightEncoder(void);

  // get left/right encoder distance since last reset
  float GetLeftEncoderDistance(void); 
  float GetRightEncoderDistance(void);

};
