/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveTurnToAngle.h"
#include "subsystems/MainDrive.h"
#include "subsystems/NavX.h"
#include "Robot.h"
#include "RobotMap.h"

// constructor - Turn robot by fixed angle, with speed limit
// Inputs: Angle +/- deg, Speed 0 to 1.0
DriveTurnToAngle::DriveTurnToAngle(float Angle, float Tolerance, float zSpeed, float xSpeed) {

  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_MainDrive);

  // distance drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);

  // set the parameters: Angle, tolerance, zspeed and xspeed
  // ensure speeds within acceptable tolerance, otherwise set to zero
  m_Angle = Angle;
  m_Tolerance = fabs(Tolerance);
  if (zSpeed >= 0.0 && zSpeed <=1.0)
     m_zSpeed = zSpeed;
  else
    m_zSpeed = 0.0;
  
  if (xSpeed >= -1.0 && xSpeed <=1.0)
     m_xSpeed = xSpeed;
  else
    m_xSpeed = 0.0;
}

// Called just before this Command runs the first time
void DriveTurnToAngle::Initialize() {

  // zero the gyro
  //Robot::m_NavX.ZeroYaw();

  // reset integrated error
  m_IntegratedError = 0.0;

  // set initial sample for differential error calculation
  m_PreviousYaw = Robot::m_NavX.GetYaw();
}

// Called repeatedly when this Command is scheduled to run
void DriveTurnToAngle::Execute() {

  // get the current yaw - use modulus to avoid robot spinning around unwinding its angle
  float CurrentYaw = fmod(Robot::m_NavX.GetYaw(), 360.0);

  // our current error  
  float error = m_Angle - CurrentYaw;

  if (error > 180.0)
    m_Angle -= 360.0;
  else if (error < -180.0)
    m_Angle += 360.0;

  // integrate error - do not integrate if error is over 10 deg
  if (fabs(error) >10.0) 
    m_IntegratedError = 0;
  else
    m_IntegratedError = m_IntegratedError + 0.02*error;

  // differential error
  // for speed optimization multiply instead of divicde - 1.0/0.02 = 50.0
  float DifferentialError = (CurrentYaw - m_PreviousYaw) * 50.0;

  // PI output
  float PIOutput = 0.05 * error + 0.06*m_IntegratedError - 0.005*DifferentialError;

  // apply speed limit to error output to ensure we don't turn faster than max speed given to us
  if (PIOutput > m_zSpeed)
    PIOutput = m_zSpeed;
  else if (PIOutput < -m_zSpeed)
    PIOutput = -m_zSpeed;

  // compare current angle to the desired angle
  // if within acceptable tolerance of desire angle, count up timer
  if (fabs(error)<= m_Tolerance)
    m_Timer = m_Timer + 0.02;
  else
    m_Timer = 0.0;

  // turn robot
  Robot::m_MainDrive.SetArcadeDrive(m_xSpeed, PIOutput , false);

  // update previous yaw - use to determine differential error
  m_PreviousYaw = CurrentYaw;
}

// Make this return true when this Command no longer needs to run execute()
bool DriveTurnToAngle::IsFinished() { 

  // if we have been within tolerance of target for greater than time, then we have arrived
  return (m_Timer >=0.20);
}

// Called once after isFinished returns true
void DriveTurnToAngle::End() {
    // we are finished - stop robot
    Robot::m_MainDrive.SetArcadeDrive(0.0, 0.0 , false);
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void DriveTurnToAngle::Interrupted() {}