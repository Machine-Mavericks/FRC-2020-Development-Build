/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/drive/SteerTowardsTarget.h"
#include "Robot.h"
#include "RobotMap.h"
#include "detection/TargetDetection.h"

// Constructor - approach target
SteerTowardsTarget::SteerTowardsTarget() {
  
  // This command requires use of robot drive
  Requires (&Robot::m_MainDrive);

  // distance drive command is not interruptable
  SetInterruptible(false);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void SteerTowardsTarget::Initialize() {
  // initially assume we are not yet arrived at target
  m_AtTarget = false;

  // type of target we are pursuing
  m_TargetType = Robot::m_Limelight.GetPipeline();
}

// Called repeatedly when this Command is scheduled to run
void SteerTowardsTarget::Execute() {

  // get ball target information
  TARGET_DATA target = GetTargetEstimation();

  // have we detected a ball?
  if (target.Detected == true&& target.TargetType==1) //- for now, pursue all targets same way
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

    // do we need to turn to angle?
    if (TargetAngle >=1.0 || TargetAngle <=-1.0)
      // drive towards target
      Robot::m_MainDrive.SetArcadeDrive(speed, 0.015*TargetAngle, false); // feb 17 p-gain was 0.020
    else
      // target is ahead of us, drive straight
      Robot::m_MainDrive.SetArcadeDrive(speed, 0.0, false);
  }
  else
  {
    // target has not been detected - stop robot
    Robot::m_MainDrive.SetArcadeDrive(0.0,0.0,false);
  }

}

// Return true when this Command is finished
bool SteerTowardsTarget::IsFinished() { 
  return false;
}

// Called once after isFinished returns true
void SteerTowardsTarget::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SteerTowardsTarget::Interrupted() {
  
}
