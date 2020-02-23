#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/drive/DifferentialDrive.h>
#include "subsystems/NavX.h"
#include "Robot.h"
#include "RobotMap.h"

class StraightDistance : public frc2::CommandHelper<frc2::CommandBase, StraightDistance> {
 public:

  // constructor - Turn robot by fixed distance, with speed limit
  StraightDistance(float Distance, float Tolerance, float Speed);
  
  // Called just before this Command runs the first time
  void Initialize() override;
  
  // Called repeatedly when this Command is scheduled to run
  void Execute() override;

  // Make this return true when this Command no longer needs to run execute()
  bool IsFinished() override;

  // Called once after isFinished returns true
  void End(bool interrupted) override;


  private:
  
  // distance to drive robot
  float m_Distance;
  
  // stopping tolerance
  float m_Tolerance;

  // speed limit to turn robot at
  float m_Speed;

  // integrated error
  float m_IntegratedError;

  // reference angle
  float m_ReferenceAngle;

  // previous distance error - used for differential error
  float m_PrevError;

  float m_Timer;

  // differential drive system to use for arcade mode
  DifferentialDrive *m_Drive;

};
