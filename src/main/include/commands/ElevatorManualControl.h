/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// ManualElevatorControl command allows elevator to be driven by jostick
// This is the default command for elevator

#pragma once

#include <frc/commands/Command.h>

class ElevatorManualControl : public frc::Command {
 public:
  
  // Constructor - Run once when command is created
  ElevatorManualControl();

  // Called just before this Command runs the first time
  void Initialize() override;
  
  // Called repeatedly when this Command is scheduled to run
  void Execute() override;

  // Return true when this Command no longer needs to run execute()
  bool IsFinished() override;
  
  // Called once after isFinished returns true
  void End() override;

  // Called when another command which requires one or more of the same
  // subsystems is scheduled to run
  void Interrupted() override;
};
