#include "commands/drive/StraightDistance.h"


// constructor - Turn robot by fixed distance, with speed limit
StraightDistance::StraightDistance(float Distance, float tolerance, float Speed)
{
  // Use AddRequirements here to declare subsystem dependencies
  AddRequirements(&Robot::m_MainDrive);

  // set the parameters: Angle, speed
  m_Distance = Distance;
  if (Speed >= 0.0 && Speed <=1.0)
     m_Speed = Speed;
  else
    m_Speed = 0.0;
}

// Called just before this Command runs the first time
void StraightDistance::Initialize() {

  m_Drive = new DifferentialDrive(*Robot::m_MainDrive.GetFrontLeftMotor(),
                                   *Robot::m_MainDrive.GetFrontRightMotor());

  // zero the drive encoders
  Robot::m_MainDrive.ResetLeftEncoder();
  Robot::m_MainDrive.ResetRightEncoder();
  
  //zero the gyro
  Robot::m_NavX.ZeroYaw();

  // reset integrated error
  m_IntegratedError = 0.0;

  
}

// Called repeatedly when this Command is scheduled to run
void StraightDistance::Execute() {
 
  // get the current distance
  float Distance = 0.5 * (Robot::m_MainDrive.GetLeftEncoderDistance() + Robot::m_MainDrive.GetRightEncoderDistance());

  // our current error  
  float error = m_Distance - Distance;

  // integrate error
  m_IntegratedError = m_IntegratedError + 0.02*error;
  
  // do not integrate if error is over 10 deg
  if (fabs(error) >6.0)
    m_IntegratedError = 0;

  // PI output
  float PIOutput = 0.05 * error + 0.001 * m_IntegratedError;

  // apply speed limit
  if (PIOutput > m_Speed)
    PIOutput = m_Speed;
  else if (PIOutput < -m_Speed)
    PIOutput = -m_Speed;

// apply speed limit
  if (fabs(error) < 6.0) {
  if (PIOutput > 0.15)
    PIOutput = 0.15;
  else if (PIOutput < -0.15)
    PIOutput = -0.15;
}

  // set main drive tank speeds
  if (m_Drive!=NULL)
    m_Drive->ArcadeDrive(-PIOutput, -0.05*Robot::m_NavX.GetYaw() , false);
}

// Make this return true when this Command no longer needs to run execute()
bool StraightDistance::IsFinished() { 

  float AvgDistance = 0.5 * (Robot::m_MainDrive.GetLeftEncoderDistance() + Robot::m_MainDrive.GetRightEncoderDistance());
  
  // have we travelled far enough (within 2" of target)
  if (fabs(m_Distance -AvgDistance)< 1.0 || ((m_Distance >= 0.0) && (AvgDistance > m_Distance)) || 
  ((m_Distance < 0.0) && (AvgDistance < m_Distance)))
    return true; 
  else
    return false;
}

// Called once after isFinished returns true
void StraightDistance::End(bool interrupted) {
    // we are finished - stop robot
    Robot::m_MainDrive.SetArcadeDrive(0.0, 0.0 , false);

    // finished using differential drive - delete object
  if (m_Drive !=NULL)
    delete m_Drive;
}
