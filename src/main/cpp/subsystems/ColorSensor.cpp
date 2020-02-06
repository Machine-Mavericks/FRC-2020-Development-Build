/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "subsystems/ColorSensor.h"
#include "RobotMap.h"
#include "wpi/ArrayRef.h"


// constructor - used to initialize specific hardware
ColorSensor::ColorSensor(){

/*  static constexpr auto i2cPort = frc::I2C::Port::kOnboard;

  /**
   * A Rev Color Sensor V3 object is constructed with an I2C port as a 
   * parameter. The device will be automatically initialized with default 
   * parameters.
   */
  //rev::ColorSensorV3 m_ColorSensor{i2cPort}; 
  
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

// ---------------Camera Access Functions ---------------------


// get angles to center of target
int ColorSensor::GetColor(void)
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



