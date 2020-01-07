/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CameraSwitchPipeline.h"
#include "subsystems/Limelight.h"
#include "Robot.h"

// Constructor - switches camera pipeline
// Input: Camera pipeline - 0 to 9
CameraSwitchPipeline::CameraSwitchPipeline(unsigned int Pipeline) {
  // Use Requires() here to declare subsystem dependencies
  Requires(&Robot::m_Limelight);
  Requires(&Robot::m_CameraTilt);

  // Record pipeline # to switch camera to
  m_Pipeline = Pipeline;
}

// Called once when the command executes
void CameraSwitchPipeline::Initialize() {
  Robot::m_Limelight.SetPipeline(m_Pipeline);

  if (m_Pipeline == 0)
    Robot::m_CameraTilt.SetTilt(CAMERA_TILTANGLE_CHEVRON);
  if (m_Pipeline == 1)
    Robot::m_CameraTilt.SetTilt(CAMERA_TILTANGLE_BALL);
}
