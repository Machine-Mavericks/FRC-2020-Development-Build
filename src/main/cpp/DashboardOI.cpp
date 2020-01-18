/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/WPILib.h>
#include "DashboardOI.h"
#include "Robot.h"
#include <frc/Shuffleboard/Shuffleboard.h>
#include "frc/shuffleboard/WidgetType.h"
#include "detection/TargetDetection.h"
#include "commands/DriveGoToTarget.h"
#include "commands/DriveFollowPath.h"
#include "commands/AutoRunLeft.h"
#include "commands/AutoRunRight.h"
#include "commands/AutoRunLeftFront.h"
#include "commands/AutoRunRightFront.h"
#include "commands/AutoLeftLow.h"
#include "commands/AutoRightLow.h"
//#include "commands/LH2R.h"

extern DriveGoToTarget::PATHTOTARGET tg;

// class constructor - executed upon creation of DashboardOI object
DashboardOI::DashboardOI() { }

// initialize dashboard
void DashboardOI::InitializeDashBoard(void)
{
    // initialize shuffleboard
    Robot::m_MainDrive.InitializeShuffleBoard();
    Robot::m_NavX.InitializeShuffleBoard();
    Robot::m_AirCompressor.InitializeShuffleBoard();
    Robot::m_Limelight.InitializeShuffleBoard();
    Robot::m_IntakeTilt.InitializeShuffleBoard();
    Robot::m_Elevator.InitializeShuffleBoard();
    Robot::m_CameraTilt.InitializeShuffleBoard();
    Robot::m_Snowblower.InitializeShuffleBoard();
    Robot::m_Climb.InitializeShuffleBoard();
    TargetDetectionInitializeShuffleBoard();

    // add commands to smartdashboard
    frc::SmartDashboard::PutData("Auto L. Hab2", new AutoRunLeft());
    frc::SmartDashboard::PutData("Auto R. Hab2", new AutoRunRight());
    
    frc::SmartDashboard::PutData("Auto L. F. Hab2", new AutoRunLeftFront());
    frc::SmartDashboard::PutData("Auto R. F. Hab2", new AutoRunRightFront());
    
    frc::SmartDashboard::PutData("Auto L. Hab1", new AutoLeftLow());
    frc::SmartDashboard::PutData("Auto R. Hab1", new AutoRightLow());
    

    // Commands Settings Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Commands");

    /*ShuffleboardLayout *l1 = &Tab->GetLayout("Auto L. Settings", BuiltInLayouts::kList);
    l1->WithPosition(0,0);
    l1->WithSize(1,2);
    l1->Add("Distance", 238.0);

    ShuffleboardLayout *l2 = &Tab->GetLayout("Auto L. Adjust", BuiltInLayouts::kList);
    l2->WithPosition(1,0);
    l2->WithSize(1,2);
    AutoLDistanceAdjust=l2->AddPersistent("Distance", 0.0).GetEntry();
    
    ShuffleboardLayout *l3 = &Tab->GetLayout("Auto R. Settings", BuiltInLayouts::kList);
    l3->WithPosition(2,0);
    l3->WithSize(1,2);
    l3->Add("Distance", 238.0);
    
    ShuffleboardLayout *l2 = &Tab->GetLayout("Auto L. Adjust", BuiltInLayouts::kList);
    l2->WithPosition(3,0);
    l2->WithSize(1,2);
    AutoRDistanceAdjust=l2->AddPersistent("Distance", 0.0).GetEntry(); */

}

// Update dashboard
void DashboardOI::UpdateDashBoard(void)
{   
    // update subsystem values to Shuffleboard
    Robot::m_MainDrive.UpdateShuffleBoard();
    Robot::m_NavX.UpdateShuffleBoard();
    Robot::m_AirCompressor.UpdateShuffleBoard();
    Robot::m_Limelight.UpdateShuffleBoard();
    Robot::m_IntakeTilt.UpdateShuffleBoard();
    Robot::m_Elevator.UpdateShuffleBoard();
    Robot::m_CameraTilt.UpdateShuffleBoard();
    Robot::m_Snowblower.UpdateShuffleBoard();
    Robot::m_Climb.UpdateShuffleBoard();
    TargetDetectionUpdateShuffleBoard();
    
    


    // Elevator data
    //frc::SmartDashboard::PutNumber("ElevatorTargetPosition", Robot::m_Elevator.GetElevatorTargetPresetPosition());
    //frc::SmartDashboard::PutBoolean("ElevatorAtTarget?", Robot::m_Elevator.IsElevatorAtTarget());
    //frc::SmartDashboard::PutNumber("Next Elevator Position", Robot::m_Elevator.GetElevatorNextHigherPresetPosition());
    //frc::SmartDashboard::PutNumber("Elevator Motor Current", Robot::m_Elevator.GetMotorCurrent());
    //frc::SmartDashboard::PutNumber("Elevator Encoder", Robot::m_Elevator.GetEncoderPosition());

    // intake tilt
    //frc::SmartDashboard::PutNumber("TiltEncoder", Robot::m_IntakeTilt.GetEncoderPosition());
    //frc::SmartDashboard::PutBoolean("IsFwdSwitchClosed", Robot::m_IntakeTilt.IsFwdLimitSwitchClosed());
    //frc::SmartDashboard::PutBoolean("IsRevSwitchClosed",Robot::m_IntakeTilt.IsRevLimitSwitchClosed());
    //frc::SmartDashboard::PutNumber("TiltTarget", Robot::m_IntakeTilt.GetIntakeTiltTargetAnalog());
    //frc::SmartDashboard::PutNumber("TiltCurrent", Robot::m_IntakeTilt.GetMotorCurrent());

    // claw
    //frc::SmartDashboard::PutNumber("ClawEncoder", Robot::m_Claw.GetEncoderPosition());
    //frc::SmartDashboard::PutBoolean("IsFwdSwitchClosedClaw", Robot::m_Claw.IsFwdLimitSwitchClosed());
    //frc::SmartDashboard::PutBoolean("IsRevSwitchClosedClaw",Robot::m_Claw.IsRevLimitSwitchClosed());
    //frc::SmartDashboard::PutNumber("ClawCurrent", Robot::m_Claw.GetMotorCurrent());
    //frc::SmartDashboard::PutNumber("ClawTarget", Robot::m_Claw.GetClawTargetAnalog());

    // show drive to target data
    //frc::SmartDashboard::PutNumber("Angle1", tg.Angle1);
    //frc::SmartDashboard::PutNumber("Distance1", tg.Distance1);
    //frc::SmartDashboard::PutNumber("Angle2", tg.Angle2);
    //frc::SmartDashboard::PutNumber("Distance2", tg.Distance2);
    //frc::SmartDashboard::PutNumber("CX", tg.CX);
    //frc::SmartDashboard::PutNumber("CZ", tg.CZ);
    //frc::SmartDashboard::PutNumber("XA", tg.XA);
 }
