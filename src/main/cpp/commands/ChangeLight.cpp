
#include "commands/ChangeLight.h"
#include <frc/DigitalOutput.h>
#include "Robot.h"
#include "RobotMap.h"
#include "detection/TargetDetection.h"

ChangeLight::ChangeLight() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());

  Requires (&Robot::m_IndicatorLight);
  
  // ChangeLight command is interruptible
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);

}

// Called just before this Command runs the first time
void ChangeLight::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ChangeLight::Execute() {
  TARGET_DATA target = GetTargetEstimation(); 
  // turn light on if there is a target

  if (target.Detected == true && target.XDistance != 0)
    Robot::m_IndicatorLight.ChangeLight(true);
  else
    Robot::m_IndicatorLight.ChangeLight(false);
}

// Make this return true when this Command no longer needs to run execute()
bool ChangeLight::IsFinished() { return false; }

// Called once after isFinished returns true
void ChangeLight::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ChangeLight::Interrupted() {}
