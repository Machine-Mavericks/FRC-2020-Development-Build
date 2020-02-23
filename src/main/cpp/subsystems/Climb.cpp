/*----------------------------------------------------------------------------*/
/* CopyWinch (c) 2019 FIRST. All Winchs Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climb.h"


Climb::Climb() {  

  // create motor control object - assign unique CAN address to each motor drive
  m_Motor = new WPI_TalonFX(CLIMB_MOTOR_CANID);
  
  // reset encoders
  ResetEncoder();
  }

//lift the robot
void Climb::Lift()
{
  
}

// ------------- Drive Encoder Functions -------------

// reset the encoder to 0 distance
void Climb::ResetEncoder(void)
{
  // first parameter - encoder position, second parameter PID loop ID (use 0), third is timeout (use 0)
  m_Motor->SetSelectedSensorPosition(0, 0, 0);
}

// get encoder distance since last reset
float Climb::GetEncoderDistance(void)
{
  return m_Motor->GetSelectedSensorPosition(0);
}



