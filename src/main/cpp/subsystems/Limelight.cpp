/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "subsystems/Limelight.h"
#include "RobotMap.h"
#include "wpi/ArrayRef.h"


// constructor - used to initialize specific hardware
Limelight::Limelight() : Subsystem("Limelight") {
  
    // set pointer to limelight network table
    table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

    // initialize camera to use LED mode set in current pipeline
    table->PutNumber("ledMode", 0);

    // set camera streaming mode - primary and secondary cameras are placed side-by-side
    table->PutNumber("stream", 0);

    // set initial pipeline to 0
    SetPipeline(0);
}

// default command to run with the subsystem
void Limelight::InitDefaultCommand() {}


// ---------- Camera Control Functions

// set camera's current pipeline
void Limelight::SetPipeline(unsigned int num) {
   if (num <=9)
      table->PutNumber("pipeline",num);   
}

// returns camera's current pipeline
unsigned int Limelight::GetPipeline(){
  return table->GetNumber("getpipe",0);
}


// ---------------Camera Access Functions ---------------------


// get angles to center of target
float Limelight::GetHorizontalTargetOffsetAngle()
{ return table->GetNumber("tx",0.0); }

float Limelight::GetVerticalTargetOffsetAngle()
{ return table->GetNumber("ty",0.0); }

float Limelight::GetTargetSkew()
{ return table->GetNumber("ts",0.0); }

// get camera translation vector to target
Limelight::CamTran Limelight::GetCameraTranslation() {
  // set up data structure to return
  Limelight::CamTran camtran;

  // get camera translation vector from camera
  std::vector<double> values = table->GetNumberArray("camtran", wpi::ArrayRef<double>());

  // if translation vector is valid (has 6 numbers in it) go ahead and record data in structure
  if (values.size()>=6)
  {
    camtran.x = values[0];
    camtran.y = values[1];
    camtran.z = values[2];
    camtran.pitch = values[3];
    camtran.yaw = values[4];
    camtran.roll = values[5];
  }

  // return data structure
  return camtran;
}

// get target detection time latency
float Limelight::GetLatencyContribution()
{ return table->GetNumber("tl",0.0); }

// get whether target is currently detected or not
bool Limelight::IsTargetPresent()
{ return table->GetNumber("tv", 0); }


// get target atributes
float Limelight::GetTargetArea()
{ return table->GetNumber("ta",0.0); }

int Limelight::GetShortestSide()
{ return table->GetNumber("tshort",0); }

int Limelight::GetLongestSide()
{ return table->GetNumber("tlong",0); }

int Limelight::GetHorizontalSideLength()
{ return table->GetNumber("thor",0); }

int Limelight::GetVerticalSideLength()
{ return table->GetNumber("tvert",0); }

// get raw target attributes
float Limelight::GetRawScreenspaceX0()
{  return table->GetNumber("tx0",0.0); }

float Limelight::GetRawScreenspaceX1()
{  return table->GetNumber("tx1",0.0); }

float Limelight::GetRawScreenspaceX2()
{  return table->GetNumber("tx2",0.0); }

float Limelight::GetRawScreenspaceY0()
{  return table->GetNumber("ty0",0.0); }

float Limelight::GetRawScreenspaceY1()
{  return table->GetNumber("ty1",0.0); }

float Limelight::GetRawScreenspaceY2()
{  return table->GetNumber("ty2",0.0); }

float Limelight::GetRawArea0()
{  return table->GetNumber("ta0",0.0); }

float Limelight::GetRawArea1()
{  return table->GetNumber("ta1",0.0); }

float Limelight::GetRawArea2()
{  return table->GetNumber("ta2",0.0); }

float Limelight::GetRawSkew0()
{  return table->GetNumber("ts0",0.0); }

float Limelight::GetRawSkew1()
{  return table->GetNumber("ts1",0.0); }

float Limelight::GetRawSkew2()
{ return table->GetNumber("ts2",0.0); }
