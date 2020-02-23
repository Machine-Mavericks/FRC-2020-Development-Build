/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LED.h"
#include "RobotMap.h"


LED::LED(){
    m_AddressableLED = new AddressableLED(LED_PORT);
    std::array<frc::AddressableLED::LEDData, 150> m_LEDBuffer;
    m_AddressableLED->SetLength(150); 
    m_AddressableLED->SetData(m_LEDBuffer);
    m_AddressableLED->Start();
    


}

/*void LED::SetRGB(int r, int g, int b){
    
    for (int i = 0; i < 150; i++){
        m_LEDBuffer[i].SetRGB(r, g, b);
    }

    m_AddressableLED->SetData(m_LEDBuffer);
    } */


void LED::SetRGB(int r, int g, int b){
    
    for (int i = 0; i <= 149; i++){
        m_LEDBuffer[i].SetRGB(r,g,b);
    }
    m_AddressableLED->SetData(m_LEDBuffer);
    }

