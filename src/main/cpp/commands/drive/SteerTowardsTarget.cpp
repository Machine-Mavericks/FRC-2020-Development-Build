/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// SteerTowardsTarget drive command allows robot to be driven in SteerTowardsTarget mode.
// This is the default command when robot in teleop mode

#include "commands/drive/SteerTowardsTarget.h"
#include "Robot.h"
#include <math.h>
#include "RobotMap.h"
#include "Detection/TargetDetection.h"

SteerTowardsTarget::SteerTowardsTarget() {
  // Use AddRequirements here to declare subsystem dependencies
  AddRequirements (&Robot::m_MainDrive);
  AddRequirements(&Robot::m_NavX);
  AddRequirements(&Robot::m_Limelight);

}

// Called just before this Command runs the first time
void SteerTowardsTarget::Initialize() {
   // initially assume we are not yet arrived at target
  m_AtTarget = false;

}

// Called repeatedly when this Command is scheduled to run
void SteerTowardsTarget::Execute() {
 
  // get ball target information
  TARGET_DATA target = GetTargetEstimation();

    // get throttle value from main drive
    float throttle = Robot::m_MainDrive.GetThrottle();

    // get speed to drive towards ball
    float speed = Robot::m_DriverOI.DriveJoystick->GetRawAxis(RIGHT_JOYSTICK_Y_AXIS_ID);

    // implement non-linear joystick response curves
    speed = LINEAR_WEIGHT * speed + CUBIC_WEIGHT * pow(speed, 3);

    // reduce by speed by amount of throttle
    speed = speed * throttle;

    // get angle to target
    float TargetAngle = 0;

    //get limelight pipeline
    if(Robot::m_Limelight.GetPipeline() == 4){
      TargetAngle = target.XAngle;
    }
    else{
      if (fabs(Robot::m_NavX.GetYaw()) >= 10.0){
      TargetAngle = -Robot::m_NavX.GetYaw();
      }
      else if(target.Detected == true){
      // get angle to target
      TargetAngle = target.XAngle;
      }
    }

    static float IError =0.0;
    if (fabs(TargetAngle) < 0.5)
      IError += TargetAngle * 0.001;
    else if (fabs(TargetAngle) < 5.0)
      IError += TargetAngle * 0.0001;
    else
      IError = 0.0;    

    if (IError > 0.1)
      IError =0.1;
    if (IError < -0.1)
      IError = -0.1;

    // is angle correction positive or negative?
    if (TargetAngle >=0.0)
      // drive towards target
      Robot::m_MainDrive.SetArcadeDrive(speed, std::min(0.3, IError+0.03*TargetAngle), false); // feb 17 p-gain was 0.020
    else 
      // drive towards target
      Robot::m_MainDrive.SetArcadeDrive(speed, std::max(IError+0.03*TargetAngle, -0.3), false); // feb 17 p-gain was 0.020
}

// Make this return true when this Command no longer needs to run execute()
bool SteerTowardsTarget::IsFinished() {
  // since this is default mode, always return false - command never ends
  return false;
}

// Called once after isFinished returns true
void SteerTowardsTarget::End(bool interrupted) {}

