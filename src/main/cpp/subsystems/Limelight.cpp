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
Limelight::Limelight(){
  
    // set pointer to limelight network table
    table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

    // initialize camera to use LED mode set in current pipeline
    table->PutNumber("ledMode", 0);

    // set camera streaming mode - primary and secondary cameras are placed side-by-side
    table->PutNumber("stream", 0);

    // set initial pipeline to 0
    SetPipeline(0);
}

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


// ------------- Shuffleboard Functions -------------

void Limelight::InitializeShuffleBoard(void)
{
    // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Limelight");
    
    Pipeline = Tab->Add("Pipeline", 0).WithPosition(0,0).GetEntry();
    TargetPresent = Tab->Add("Target Present", false).WithPosition(1,0).GetEntry();

    ShuffleboardLayout *l1 = &Tab->GetLayout("Target", BuiltInLayouts::kList);
    l1->WithPosition(2,0);
    l1->WithSize(1,4);
    AngleX = l1->Add("AngleX", 0.0).GetEntry();
    AngleY = l1->Add("AngleY", 0.0).GetEntry();
    Skew = l1->Add("Skew", 0.0).GetEntry(); 

    ShuffleboardLayout *l2 = &Tab->GetLayout("Dimensions", BuiltInLayouts::kList);
    l2->WithPosition(3,0);
    l2->WithSize(1,5);
    Area = l2->Add("Area", 0.0).GetEntry(); 
    Short = l2->Add("Short", 0.0).GetEntry(); 
    Long = l2->Add("Long", 0.0).GetEntry(); 
    Hor = l2->Add("Hor", 0.0).GetEntry(); 
    Vert = l2->Add("Vert", 0.0).GetEntry(); 

    ShuffleboardLayout *l3 = &Tab->GetLayout("CamTran", BuiltInLayouts::kList);
    l3->WithPosition(4,0);
    l3->WithSize(1,5);
    X = l3->Add("X", 0.0).GetEntry();
    Y = l3->Add("Y", 0.0).GetEntry(); 
    Z = l3->Add("Z", 0.0).GetEntry(); 
    Pitch = l3->Add("Pitch", 0.0).GetEntry(); 
    Yaw = l3->Add("Yaw", 0.0).GetEntry(); 
    Roll = l3->Add("Roll", 0.0).GetEntry();

    HexReady = Tab->Add("Target Ready", false).WithPosition(5,0).GetEntry();
    ShuffleboardLayout *l4 = &Tab->GetLayout("Target Info", BuiltInLayouts::kList);
    l4->WithPosition(5,1);
    l4->WithSize(1,2);
    Hex_X = l4->Add("XAngle", 0.0).GetEntry();
    Hex_Distance = l4->Add("Distance", 0.0).GetEntry();

}

// update shuffle board with current values
void Limelight::UpdateShuffleBoard(void)
{
  
  Pipeline.SetDouble(GetPipeline());
  TargetPresent.SetBoolean(IsTargetPresent());
  
  AngleX.SetDouble(GetHorizontalTargetOffsetAngle());
  AngleY.SetDouble(GetVerticalTargetOffsetAngle());
  Skew.SetDouble(GetTargetSkew());

  Area.SetDouble(GetTargetArea());
  Short.SetDouble(GetShortestSide());
  Long.SetDouble(GetLongestSide());
  Hor.SetDouble(GetHorizontalSideLength());
  Vert.SetDouble(GetVerticalSideLength());

  Limelight::CamTran vector = GetCameraTranslation();
  X.SetDouble(vector.x);
  Y.SetDouble(vector.y);
  Z.SetDouble(vector.z);
  Pitch.SetDouble(vector.pitch);
  Yaw.SetDouble(vector.yaw);
  Roll.SetDouble(vector.roll);

  Limelight::HEXTARGET_DATA data = GetTargetEstimation();
  HexReady.SetBoolean(data.Detected && (fabs(data.XAngle)<1.0));
  Hex_X.SetDouble(data.XAngle);
  Hex_Distance.SetDouble(data.ZDistance);
}




// ---------- Target Detection Routines ----------


Limelight::HEXTARGET_DATA Limelight::GetTargetEstimation(void)
{
    HEXTARGET_DATA target;

    // assume no target detected unless proven otherwise
    target.Detected = false;
    
    // determine if camera has acquired a target
    bool detected = IsTargetPresent();

    // get target side lengths
    float vert = GetVerticalSideLength();
    float hor = GetHorizontalSideLength();

    // get shortest side
    float shortside = GetShortestSide();

    // get target area of target (in sq pixels)
    float area = vert*hor;

    if (detected==true && area > MIN_HEX_DETECTION_AREA && shortside > MIN_HEX_VERT_SIZE)
    {
        target.Detected = true;
        target.TargetType = 0;
        target.Area = area;
        target.XAngle = GetHorizontalTargetOffsetAngle();
        target.ZDistance = (412.0 / vert);
    }
 
    // return target data
    return target;
}
