/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveSteerTowardsTarget.h"
#include "Robot.h"
#include "RobotMap.h"
#include "detection/TargetDetection.h"

// Constructor - approach target
DriveSteerTowardsTarget::DriveSteerTowardsTarget() {
  
  // This command requires use of robot drive
  Requires (&Robot::m_MainDrive);
  Requires (&Robot::m_IntakeTilt);
  Requires (&Robot::m_Snowblower);
  Requires (&Robot::m_Elevator);

  // distance drive command is not interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void DriveSteerTowardsTarget::Initialize() {
  // initially assume we are not yet arrived at target
  m_AtTarget = false;

  // type of target we are pursuing
  m_TargetType = Robot::m_Limelight.GetPipeline();

  // if we are pursing a ball, lower and turn on intake
  if (m_TargetType==1)
  {
    Robot::m_Elevator.SetElevatorPresetPosition(0);
    Robot::m_IntakeTilt.SetIntakeTiltTargetPosition(2);
    Robot::m_Snowblower.SetMaxMotorCurrent(SNOWBLOWER_CURRENT_LIMIT_IN);
    Robot::m_Snowblower.SetMotorSpeed(-1.0);
  }
}

// Called repeatedly when this Command is scheduled to run
void DriveSteerTowardsTarget::Execute() {

  // get ball target information
  TARGET_DATA target = GetTargetEstimation();

  // have we detected a ball?
  if (target.Detected == true) //- for now, pursue all targets same way
  {
    // target has been detected

    // get joystick right throttle to control maximum robot speed
    // adjust throttle to give value between 0 and +1.0
    // use negative of throttle so that +1 represents throttle forward position
    float throttle = 0.5 * (1.0 + -Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_THROTTLE_AXIS_ID));

    // get speed to drive towards ball
    float speed = Robot::m_DriverOI.LeftJoystick->GetRawAxis(JOYSTICK_Y_AXIS_ID);

    // implement non-linear joystick response curves
    speed = LINEAR_WEIGHT * speed + CUBIC_WEIGHT * pow(speed, 3);

    // reduce by speed by amount of throttle
    speed = speed * throttle;

    // get angle to target
    float TargetAngle = target.XAngle;

    // is angle correction positive or negative?
    if (TargetAngle >=0.0)
      // drive towards target
      Robot::m_MainDrive.SetArcadeDrive(speed, std::min(0.2, 0.02*TargetAngle), false); // feb 17 p-gain was 0.020
    else 
      // drive towards target
      Robot::m_MainDrive.SetArcadeDrive(speed, std::max(0.02*TargetAngle, -0.2), false); // feb 17 p-gain was 0.020
   
  }
  else
  {
    // target has not been detected - stop robot
    Robot::m_MainDrive.SetArcadeDrive(0.0,0.0,false);
  }

}

// Return true when this Command is finished
bool DriveSteerTowardsTarget::IsFinished() { 
  return false;
}

// Called once after isFinished returns true
void DriveSteerTowardsTarget::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveSteerTowardsTarget::Interrupted() {
  
}
