/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Odometry.h"
#include "Robot.h"


Odometry::Odometry() {  

    // create robot odometry - set to zero
    Rotation2d rotation(units::radian_t(0.0));
    Pose2d position(units::meter_t(0.0), units::meter_t(0.0), rotation);
    m_Odometry = new DifferentialDriveOdometry(rotation, position);
 
  }

// initialize robot odometry based - use shuffleboard settings and current gyro angle
void Odometry::Initialize() {
    SetPosition(InitialX.GetDouble(0.0),
                InitialY.GetDouble(0.0),
                Robot::m_NavX.GetYaw());
}

// used to set or reset odometry
// function assumes robot and gyro angle are the same
// x, y displacement in m
// angle in deg
void Odometry::SetPosition(float x, float y, float angle){

    // set odometry rotation
    Rotation2d rotation(units::radian_t(angle*degToRad));
   
    // set robot position - assume same angle as gyro
    Pose2d position(units::meter_t(x), units::meter_t(y), rotation);
   
    // set robot odometry
    m_Odometry->ResetPosition(position, rotation);
}


// update current robot odometry 
void Odometry::Update(){

    // create rotation object and populate with current gyro angle (radians)
    Rotation2d rotation(units::radian_t(Robot::m_NavX.GetYaw()*degToRad));

    // set distances (in m)
    units::meter_t left (Robot::m_MainDrive.GetLeftEncoderDistance()*0.0254);
    units::meter_t right (Robot::m_MainDrive.GetRightEncoderDistance()*0.0254);

    // update odometry
    m_Odometry->Update(rotation, left, right);
}

// return current odometry x displacement (in m)
float Odometry::GetX(){
  return m_Odometry->GetPose().Translation().X().to<float>();
}


float Odometry::GetY(){
  return m_Odometry->GetPose().Translation().Y().to<float>();
}

float Odometry::GetAngle(){
  return m_Odometry->GetPose().Rotation().Degrees().to<float>();
}

// ------------- Shuffleboard Functions -------------

void Odometry::InitializeShuffleBoard(void)
{
    // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Odometry");
    
    ShuffleboardLayout *l1 = &Tab->GetLayout("Odometry", BuiltInLayouts::kList);
    l1->WithPosition(0,0);
    l1->WithSize(1,3);
    RobotX = l1->Add("X", 0.0).GetEntry();
    RobotY = l1->Add("Y", 0.0).GetEntry();
    RobotAngle = l1->Add("Angle(deg)", 0.0).GetEntry();

    ShuffleboardLayout *l2 = &Tab->GetLayout("Initial Position", BuiltInLayouts::kList);
    l2->WithPosition(4,0);
    l2->WithSize(1,2);
    InitialX=l2->AddPersistent("X", 0.0).GetEntry();
    InitialY=l2->AddPersistent("Y", 0.0).GetEntry();
 
}

// update shuffle board with current odometry values
void Odometry::UpdateShuffleBoard(void)
{
    // write current robot odometry
    RobotX.SetDouble(GetX());
    RobotY.SetDouble(GetY());
    RobotAngle.SetDouble(GetAngle()); 
}
