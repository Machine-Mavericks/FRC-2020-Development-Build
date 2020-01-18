#include "commands/DriveStraightTilStopped.h"
#include "subsystems/MainDrive.h"
#include "subsystems/NavX.h"
#include "Robot.h"
#include "RobotMap.h"

// constructor - Turn robot by fixed Distance, with speed limit
DriveStraightTilStopped::DriveStraightTilStopped(float Distance, float Speed)
{

  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_MainDrive);

  //Distance drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);

  // set the parameters: Angle, speed
  m_Distance=Distance;
  if (Speed >= 0.0 && Speed <=1.0)
     m_Speed = Speed;
  else
    m_Speed = 0.0;

}

// Called just before this Command runs the first time
void DriveStraightTilStopped::Initialize() {

  // zero the drive encoders
  Robot::m_MainDrive.ResetLeftEncoder();
  Robot::m_MainDrive.ResetRightEncoder();
  
  //zero the gyro
  //Robot::m_NavX.ZeroYaw();
  m_ReferenceAngle = Robot::m_NavX.GetYaw();

  // reset integrated error
  m_IntegratedError = 0.0;

  m_Timer1 = 0.0;
  m_Timer = 0.0;
  m_LastAccelX = Robot::m_NavX.GetAccelX();;
  m_LastAccelY = Robot::m_NavX.GetAccelY();;
  m_CollisionDetected = false;
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightTilStopped::Execute() {
 
  // get the current Distance
  float Distance = 0.5 * (Robot::m_MainDrive.GetLeftEncoderDistance() + Robot::m_MainDrive.GetRightEncoderDistance());

  // our current error  
  float error = m_Distance-Distance;

  // integrate error
  m_IntegratedError = m_IntegratedError + 0.02*error;
  
  // do not integrate if error is over 10 deg
  if (fabs(error) >8.0)
    m_IntegratedError = 0;

  // PI output
  float PIOutput = 0.05 * error + 0.05 * m_IntegratedError;

  // apply speed limit
  if (PIOutput > m_Speed)
    PIOutput = m_Speed;
  else if (PIOutput < -m_Speed)
    PIOutput = -m_Speed;

// apply speed limit
  //if (fabs(error) < 6.0) {
  //if (PIOutput > 0.15)
  // PIOutput = 0.15;
  //else if (PIOutput < -0.15)
  //  PIOutput = -0.15;

  // determine error between our reference heading and current heating
  float AngleError = m_ReferenceAngle - Robot::m_NavX.GetYaw(); 

  // drive robot
  Robot::m_MainDrive.SetArcadeDrive(-PIOutput, 0.05*AngleError , false);

  
  float Avgdistance = 0.5 * (Robot::m_MainDrive.GetLeftEncoderDistance() + Robot::m_MainDrive.GetRightEncoderDistance());
  

  // have we travelled far enough (within 1" of target)
  if (fabs(m_Distance-Avgdistance)< 1.0 )
    m_Timer =m_Timer + 0.02;
  else
    m_Timer =  0.0;

  
  if (fabs(Robot::m_MainDrive.GetLeftEncoderSpeed()) <= 0.1 || fabs(Robot::m_MainDrive.GetRightEncoderSpeed()) <= 0.1) {
        m_Timer1 =m_Timer1 + 0.02;
  }
  else {
    m_Timer1 =  0.0;
  }


  double currentAccelX =  Robot::m_NavX.GetAccelX();
  double currentJerkX = (currentAccelX - m_LastAccelX)*50.0;
  m_LastAccelX = currentAccelX;
  double currentAccelY = Robot::m_NavX.GetAccelY();
  double currentJerkY = (currentAccelY - m_LastAccelY)*50.0;
  m_LastAccelY = currentAccelY;

  if ( ( fabs(currentJerkX) > COLLISION_THRESHOLD_DELTA_G ) || ( fabs(currentJerkY) > COLLISION_THRESHOLD_DELTA_G) ) {
        if (m_Distance > 0) {
          m_CollisionDetected = true;
        }
  }

}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightTilStopped::IsFinished() { 

  //float AvgDistance= 0.5 * (Robot::m_MainDrive.GetLeftEncoderDistance() + Robot::m_MainDrive.GetRightEncoderDistance());
  //return (m_Timer1 > 0.2 || m_CollisionDetected || (fabs(m_Distance-AvgDistance)< 1.0 ));
  return (m_Timer > 0.2 || m_Timer1 >0.2);
  //return (m_Timer1>0.2 || m_Timer>0.2 || m_CollisionDetected);
  // have we travelled far enough (within 2" of target)
  //if (fabs(m_Distance-AvgDistance)< 1.0 )
  //  return true; 
  //else
  //  return false;
}

// Called once after isFinished returns true
void DriveStraightTilStopped::End() {
    // we are finished - stop robot
    Robot::m_MainDrive.SetArcadeDrive(0.0, 0.0 , false);
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void DriveStraightTilStopped::Interrupted() {}