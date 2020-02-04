/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Tank drive command allows robot to be driven in tank mode.
// This is the default command when robot in teleop mode

#include "commands/drive/Tank.h"
#include "Robot.h"
#include <math.h>
#include "RobotMap.h"

<<<<<<< Updated upstream
Tank::Tank() {
  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_MainDrive);
=======
SteerTowardsTarget::SteerTowardsTarget() {
  // Use AddRequirements here to declare subsystem dependencies
  AddRequirements (&Robot::m_MainDrive);
  AddRequirements(&Robot::m_NavX);
>>>>>>> Stashed changes

  // tank drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void Tank::Initialize() {}

// Called repeatedly when this Command is scheduled to run
<<<<<<< Updated upstream
void Tank::Execute() {
  // create variables for left and right joystick y axes
  float raw_left_y, raw_right_y, left_y, right_y, throttle;
=======
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
>>>>>>> Stashed changes

  // get joystick y values from joystick
  raw_left_y = Robot::m_DriverOI.LeftJoystick->GetRawAxis(JOYSTICK_Y_AXIS_ID );
  raw_right_y = Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_Y_AXIS_ID );

  // get joystick right throttle to control maximum robot speed
  // adjust throttle to give value between 0 and +1.0
  // use negative of throttle so that +1 represents throttle forward position
  throttle = 0.5 * (1.0 + -Robot::m_DriverOI.RightJoystick->GetRawAxis(JOYSTICK_THROTTLE_AXIS_ID));

  // implement non-linear joystick response curves
  right_y = LINEAR_WEIGHT * raw_right_y + CUBIC_WEIGHT * pow(raw_right_y, 3); 
  left_y = LINEAR_WEIGHT * raw_left_y + CUBIC_WEIGHT * pow(raw_left_y, 3); 

<<<<<<< Updated upstream
  // apply throttle control (scaling factor) to both left and right values.
  right_y = right_y * throttle;
  left_y = left_y * throttle;

  // set main drive tank speeds
  Robot::m_MainDrive.SetTankDrive (left_y, right_y);
=======
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
>>>>>>> Stashed changes
}

// Make this return true when this Command no longer needs to run execute()
bool Tank::IsFinished() {
  // since this is default mode, always return false - command never ends
  return false;
}

// Called once after isFinished returns true
void Tank::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Tank::Interrupted() {}
