/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/WPILib.h>
#include "DashboardOI.h"
#include "Robot.h"
#include "detection/TargetDetection.h"
#include "commands/drive/GoToTarget.h"

extern GoToTarget::PATHTOTARGET tg;
extern TARGET_DATA FilteredTarget;

// class constructor - executed upon creation of DashboardOI object
DashboardOI::DashboardOI() { }

// Update dashboard
void DashboardOI::UpdateDashBoard(void)
{
    // Show Target data
    TARGET_DATA target = GetTargetEstimation();
    frc::SmartDashboard::PutBoolean("Ball Detected?", target.Detected&&target.TargetType==1);
    frc::SmartDashboard::PutBoolean("Chevron Detected?", target.Detected&&target.TargetType==0);    
    frc::SmartDashboard::PutNumber("Target Distance", target.ZDistance);
    frc::SmartDashboard::PutNumber("Target Angle", target.XAngle);
    frc::SmartDashboard::PutNumber("Target Area", target.Area);
    
    
    //Show left/right encoder distances 
    frc::SmartDashboard::PutNumber("Left Encoder", Robot::m_MainDrive.GetLeftEncoderDistance());
    frc::SmartDashboard::PutNumber("Right Encoder", Robot::m_MainDrive.GetRightEncoderDistance());
  
    // Show robot NavX gyro data
    frc::SmartDashboard::PutNumber("Yaw", Robot::m_NavX.GetYaw());
    //frc::SmartDashboard::PutNumber("Roll", Robot::m_NavX.GetRoll());
    //frc::SmartDashboard::PutNumber("Pitch", Robot::m_NavX.GetPitch());

    // Show Limelight data
    //frc::SmartDashboard::PutNumber("Target Present?", Robot::m_Limelight.IsTargetPresent());
    //frc::SmartDashboard::PutNumber("Horizontal Target Offset Angle", Robot::m_Limelight.GetHorizontalTargetOffsetAngle());
    //frc::SmartDashboard::PutNumber("Vertical Target Offset Angle", Robot::m_Limelight.GetVerticalTargetOffsetAngle());
    //frc::SmartDashboard::PutNumber("Target Area", Robot::m_Limelight.GetTargetArea());
    //frc::SmartDashboard::PutNumber("Target Skew", Robot::m_Limelight.GetTargetSkew());

    /*frc::SmartDashboard::PutNumber("Latency", Robot::m_Limelight.GetLatencyContribution());
    frc::SmartDashboard::PutNumber("Shortest Side", Robot::m_Limelight.GetShortestSide());
    frc::SmartDashboard::PutNumber("Longest Side", Robot::m_Limelight.GetLongestSide());
    frc::SmartDashboard::PutNumber("Horizontal Side", Robot::m_Limelight.GetHorizontalSideLength());
    frc::SmartDashboard::PutNumber("Vertical Side", Robot::m_Limelight.GetVerticalSideLength());
    frc::SmartDashboard::PutNumber("Pipeline", Robot::m_Limelight.GetPipeline());

*/
    // Show limelight camera translation vector
    Limelight::CamTran vector = Robot::m_Limelight.GetCameraTranslation();
    frc::SmartDashboard::PutNumber("Camtran x", vector.x);
    frc::SmartDashboard::PutNumber("Camtran y", vector.y);
    frc::SmartDashboard::PutNumber("Camtran z", vector.z);
    frc::SmartDashboard::PutNumber("Camtran pitch", vector.pitch);
    frc::SmartDashboard::PutNumber("Camtran yaw", vector.yaw);
    frc::SmartDashboard::PutNumber("Camtran roll", vector.roll);

    // show drive to target data
    frc::SmartDashboard::PutNumber("Angle1", tg.Angle1);
    frc::SmartDashboard::PutNumber("Distance1", tg.Distance1);
    frc::SmartDashboard::PutNumber("Angle2", tg.Angle2);
    frc::SmartDashboard::PutNumber("Distance2", tg.Distance2);
    frc::SmartDashboard::PutNumber("CX", tg.CX);
    frc::SmartDashboard::PutNumber("CZ", tg.CZ);
    frc::SmartDashboard::PutNumber("XA", tg.XA);

    // show filtered camera data
    frc::SmartDashboard::PutBoolean("Filtered Detect", FilteredTarget.Detected);
    frc::SmartDashboard::PutNumber("Filtered XDistance", FilteredTarget.XDistance);
    frc::SmartDashboard::PutNumber("Filtered ZDistance", FilteredTarget.ZDistance);
    frc::SmartDashboard::PutNumber("Filtered XAngle", FilteredTarget.XAngle);

 }
