/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/WoF.h"
#include "Robot.h"


WoF::WoF() {  

    // create individual motor control objects - assign unique CAN address to each motor drive
    m_Motor = new WPI_TalonFX(WOF_MOTOR_CANID);

    // configure motor drives with factory default settings
    m_Motor->ConfigFactoryDefault();
  
    // reset encoder
    ResetEncoder();

    // set pointer to ColorSensor network table
    table = nt::NetworkTableInstance::GetDefault().GetTable("ColorSensor");

    
    kBlueTarget = Color(0.143, 0.427, 0.429);
    kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    kRedTarget = frc::Color(0.561, 0.232, 0.114);
    kYellowTarget = frc::Color(0.361, 0.524, 0.113);
  
    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget); 

  }

// get angles to center of target
int WoF::GetColor(void)
{ 
  frc::Color detectedColor = m_ColorSensor.GetColor();
    /**
     * Run the color match algorithm on our detected color
     */
    int colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

    if (matchedColor == kBlueTarget) {
      colorString = 3; //Blue
    } else if (matchedColor == kRedTarget) {
      colorString = 1; //Red
    } else if (matchedColor == kGreenTarget) {
      colorString = 2; //Green
    } else if (matchedColor == kYellowTarget) {
      colorString = 4; //Yellow
    } else {
      colorString = 0; //unknown
    } 
    return colorString;
}

// reset the left encoder to 0 distance
void WoF::ResetEncoder(void)
{
  // first parameter - encoder position, second parameter PID loop ID (use 0), third is timeout (use 0)
  m_Motor->SetSelectedSensorPosition(0, 0, 0);
}



