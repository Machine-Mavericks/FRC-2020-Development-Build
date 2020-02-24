/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LED.h"
#include "RobotMap.h"


LED::LED(){
  // create addressable LED controls
  m_AddressableLED = new AddressableLED(LED_PORT);
  m_AddressableLED->SetLength(LEDLENGTH);

  // create fixed colours  
  for (int i = 0; i <= 149; ++i)
  { 
    m_BlueLEDs[i].SetRGB(0, 0, 255);  
    m_OrangeLEDs[i].SetRGB(255, 165, 0); 
    m_LEDsOff[i].SetRGB(0, 0, 0);
  }
  
  // initially turn LEDs off
  SetLEDsOff();
  
  // enable LEDs
  m_AddressableLED->Start();
}

// preset colours
void LED::SetLEDsBlue(void) { m_AddressableLED->SetData(m_BlueLEDs); }

void LED::SetLEDsOrange(void) { m_AddressableLED->SetData(m_OrangeLEDs); }

void LED::SetLEDsOff(void) {  m_AddressableLED->SetData(m_LEDsOff); }
