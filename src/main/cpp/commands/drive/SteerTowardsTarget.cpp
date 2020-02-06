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

  // SteerTowardsTarget drive command is interruptable
  //SetInterruptible(true);
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

  // have we detected a ball?
 // if (target.Detected == true) //- for now, pursue all targets same way
  //{
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
    float TargetAngle = 0;

    if (fabs(Robot::m_NavX.GetYaw()) >= 10.0){
      TargetAngle = -Robot::m_NavX.GetYaw();
    }
    else if(target.Detected == true){
      // get angle to target
      TargetAngle = target.XAngle;
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

    //static float LastAngle = 0.0;
    //float DError=0.0;
    //if (fabs(TargetAngle) < 5.0)
    //  DError = 1.0* (TargetAngle - LastAngle);
    //LastAngle = TargetAngle;

    // is angle correction positive or negative?
    if (TargetAngle >=0.0)
      // drive towards target
      Robot::m_MainDrive.SetArcadeDrive(speed, std::min(0.3, IError+0.03*TargetAngle), false); // feb 17 p-gain was 0.020
    else 
      // drive towards target
      Robot::m_MainDrive.SetArcadeDrive(speed, std::max(IError+0.03*TargetAngle, -0.3), false); // feb 17 p-gain was 0.020
   
  /* }
 else
  {
    // target has not been detected - stop robot
    Robot::m_MainDrive.SetArcadeDrive(0.0,0.0,false);
  }*/
}

// Make this return true when this Command no longer needs to run execute()
bool SteerTowardsTarget::IsFinished() {
  // since this is default mode, always return false - command never ends
  return false;
}

// Called once after isFinished returns true
void SteerTowardsTarget::End(bool interrupted) {}

