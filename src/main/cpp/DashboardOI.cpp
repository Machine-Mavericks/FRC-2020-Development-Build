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
#include "subsystems/ColorSensor.h"

extern GoToTarget::PATHTOTARGET tg;
extern TARGET_DATA FilteredTarget;

// class constructor - executed upon creation of DashboardOI object
DashboardOI::DashboardOI() { }

// Update dashboard
void DashboardOI::UpdateDashBoard(void)
{
<<<<<<< Updated upstream
    //Color Sensor Data
    frc::SmartDashboard::PutNumber("Matched Colour", Robot::m_ColorSensor.GetColor());
=======
    // initialize shuffleboard
    Robot::m_MainDrive.InitializeShuffleBoard();
    Robot::m_NavX.InitializeShuffleBoard();
    Robot::m_Limelight.InitializeShuffleBoard();
    //Robot::m_AirCompressor.InitializeShuffleBoard();
    
    //Robot::m_IntakeTilt.InitializeShuffleBoard();
    //Robot::m_Elevator.InitializeShuffleBoard();
    //Robot::m_CameraTilt.InitializeShuffleBoard();
    //Robot::m_Snowblower.InitializeShuffleBoard();
    //Robot::m_Climb.InitializeShuffleBoard();
    //TargetDetectionInitializeShuffleBoard();

    // add commands to smartdashboard
    //frc::SmartDashboard::PutData("Auto L. Hab2", new AutoRunLeft());
    //frc::SmartDashboard::PutData("Auto R. Hab2", new AutoRunRight());
    
    //frc::SmartDashboard::PutData("Auto L. F. Hab2", new AutoRunLeftFront());
    //frc::SmartDashboard::PutData("Auto R. F. Hab2", new AutoRunRightFront());
    
    //frc::SmartDashboard::PutData("Auto L. Hab1", new AutoLeftLow());
    //frc::SmartDashboard::PutData("Auto R. Hab1", new AutoRightLow());
    

    // Commands Settings Tab
    //ShuffleboardTab *Tab = &Shuffleboard::GetTab("Commands");
>>>>>>> Stashed changes


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

<<<<<<< Updated upstream
    /*frc::SmartDashboard::PutNumber("Latency", Robot::m_Limelight.GetLatencyContribution());
    frc::SmartDashboard::PutNumber("Shortest Side", Robot::m_Limelight.GetShortestSide());
    frc::SmartDashboard::PutNumber("Longest Side", Robot::m_Limelight.GetLongestSide());
    frc::SmartDashboard::PutNumber("Horizontal Side", Robot::m_Limelight.GetHorizontalSideLength());
    frc::SmartDashboard::PutNumber("Vertical Side", Robot::m_Limelight.GetVerticalSideLength());
    frc::SmartDashboard::PutNumber("Pipeline", Robot::m_Limelight.GetPipeline());
=======
// Update dashboard
void DashboardOI::UpdateDashBoard(void)
{   
    // update subsystem values to Shuffleboard
    Robot::m_MainDrive.UpdateShuffleBoard();
    Robot::m_NavX.UpdateShuffleBoard();
    Robot::m_Limelight.UpdateShuffleBoard();
    //Robot::m_AirCompressor.UpdateShuffleBoard();
    //Robot::m_IntakeTilt.UpdateShuffleBoard();
    //Robot::m_Elevator.UpdateShuffleBoard();
    //Robot::m_CameraTilt.UpdateShuffleBoard();
    //Robot::m_Snowblower.UpdateShuffleBoard();
    //Robot::m_Climb.UpdateShuffleBoard();
    //TargetDetectionUpdateShuffleBoard();
    
    // Elevator data
    //frc::SmartDashboard::PutNumber("ElevatorTargetPosition", Robot::m_Elevator.GetElevatorTargetPresetPosition());
    //frc::SmartDashboard::PutBoolean("ElevatorAtTarget?", Robot::m_Elevator.IsElevatorAtTarget());
    //frc::SmartDashboard::PutNumber("Next Elevator Position", Robot::m_Elevator.GetElevatorNextHigherPresetPosition());
    //frc::SmartDashboard::PutNumber("Elevator Motor Current", Robot::m_Elevator.GetMotorCurrent());
    //frc::SmartDashboard::PutNumber("Elevator Encoder", Robot::m_Elevator.GetEncoderPosition());
>>>>>>> Stashed changes

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
