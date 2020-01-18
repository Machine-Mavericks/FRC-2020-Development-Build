#include "commands/DriveStraightDistance.h"
#include "subsystems/MainDrive.h"
#include "subsystems/NavX.h"
#include "Robot.h"
#include "RobotMap.h"

// constructor - Turn robot by fixed distance, with speed limit
DriveStraightDistance::DriveStraightDistance(float Distance, float Tolerance, float Speed)
{

  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_MainDrive);

  // distance drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);

  // set the parameters: Angle, speed
  m_Distance = Distance;
  m_Tolerance = Tolerance;
  if (Speed >= 0.0 && Speed <=1.0)
     m_Speed = Speed;
  else
    m_Speed = 0.0;
}

// Called just before this Command runs the first time
void DriveStraightDistance::Initialize() {

  // zero the drive encoders
  Robot::m_MainDrive.ResetLeftEncoder();
  Robot::m_MainDrive.ResetRightEncoder();
  
  //zero the gyro
  //Robot::m_NavX.ZeroYaw();
  m_ReferenceAngle = Robot::m_NavX.GetYaw();

  // reset integrated error
  m_IntegratedError = 0.0;

  m_Timer = 0.0;

  m_PrevError = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightDistance::Execute() {
 
  // get the current distance
  float Distance = 0.5 * (Robot::m_MainDrive.GetLeftEncoderDistance() + Robot::m_MainDrive.GetRightEncoderDistance());

  // our current error  
  float error = m_Distance - Distance;

  // integrate error
  m_IntegratedError = m_IntegratedError + 0.02*error;
  
  // differential error
  float DifferentialError = (error - m_PrevError)*50.0;

  // do not integrate or differentiate if error is over 12 in
  if (fabs(error) >=12.0) {
    m_IntegratedError = 0.0;
    DifferentialError = 0.0;
  }
// 0.05 and 0.10 diff
  // PI output
  float PIOutput = 0.06 * error + 0.12 * m_IntegratedError + 0.012 * DifferentialError;

  // apply speed limit
  if (PIOutput > m_Speed)
    PIOutput = m_Speed;
  else if (PIOutput < -m_Speed)
    PIOutput = -m_Speed;

// apply speed limit
  //if (fabs(error) < 6.0) {
  //if (PIOutput > 0.15)
  //  PIOutput = 0.15;
  //else if (PIOutput < -0.15)
  //  PIOutput = -0.15;

  // determine error between our reference heading and current heating
  float AngleError = m_ReferenceAngle - Robot::m_NavX.GetYaw(); 

  // drive robot
  Robot::m_MainDrive.SetArcadeDrive(-PIOutput, 0.05*AngleError , false);

  float AvgDistance = 0.5 * (Robot::m_MainDrive.GetLeftEncoderDistance() + Robot::m_MainDrive.GetRightEncoderDistance());

  // have we travelled far enough (within 1" of target)
  if (fabs(m_Distance -AvgDistance)< m_Tolerance )
    m_Timer =m_Timer + 0.02;
  else
    m_Timer =  0.0;
    
  // set previous distance error
  m_PrevError = error;
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightDistance::IsFinished() { 

  //float AvgDistance = 0.5 * (Robot::m_MainDrive.GetLeftEncoderDistance() + Robot::m_MainDrive.GetRightEncoderDistance());
  
  return (m_Timer>=0.2);
  // have we travelled far enough (within 2" of target)
  //if (fabs(m_Distance -AvgDistance)< 1.0 )
  //  return true; 
  //else
  //  return false;
}

// Called once after isFinished returns true
void DriveStraightDistance::End() {
    // we are finished - stop robot
    Robot::m_MainDrive.SetArcadeDrive(0.0, 0.0 , false);
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void DriveStraightDistance::Interrupted() {}