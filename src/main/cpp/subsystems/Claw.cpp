/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Claw.h"
#include "RobotMap.h"

Claw::Claw() : Subsystem("Claw") {

  // create individual motor control objects- assign unique CAN adress to motor drive
  m_Motor = new WPI_TalonSRX(CLAW_MOTOR_CANID);

  // configure motor drive with factory default settings
  m_Motor->ConfigFactoryDefault();

  // select quadrature encoder (first parameter) as primary feedback sensor (second parameter=0)
  // Third parameter kTimeoutMs is timeout to wait for Talon to confirm update - set to 0 for no checking
  m_Motor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);

  // sets direction of the encoder - set to true to to change count direction
  m_Motor->SetSensorPhase(false);

  // sets direction of the motr drive - set to true to invert direction
  m_Motor->SetInverted(true);

  // set nominal and peak outputs of drive 
  // nominal = 0, peak is +1 or -1 depending on direction
  // second parameter is timeout (use 0)
  m_Motor->ConfigNominalOutputForward(0, 0);
  m_Motor->ConfigNominalOutputReverse(0, 0);
  m_Motor->ConfigPeakOutputForward (CLAW_DRIVE_FULL_VLTG_FWD, 0);
  m_Motor->ConfigPeakOutputReverse (-CLAW_DRIVE_FULL_VLTG_REV, 0);

  // Set motor maximum current level to limit torque
  m_Motor->ConfigContinuousCurrentLimit(CLAW_CURRENT_LIMIT);

  // Set motor short-term maximum current level and time - to provide sufficient power to motor for acceleration
  //m_Motor->ConfigPeakCurrentLimit(4,0);
  //m_Motor->ConfigPeakCurrentDuration(500,0);

  // enable motor current limits supervision
  m_Motor->EnableCurrentLimit(true);

  // set up forward direction soft (software) limit - set to maximum allowed encoder pulse counts at Claw top
  m_Motor->ConfigForwardSoftLimitEnable(false,0);
  m_Motor->ConfigForwardSoftLimitThreshold(CLAW_SOFT_LIMIT_MAX);

  // set up reverse direction soft limit - assumes encoder pulse at bottom is 0
  m_Motor->ConfigReverseSoftLimitEnable(false, 0);
  m_Motor->ConfigReverseSoftLimitThreshold(CLAW_SOFT_LIMIT_MIN); 

   // configure limit switch - as normally open
	m_Motor->ConfigReverseLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_FeedbackConnector,LimitSwitchNormal::LimitSwitchNormal_NormallyOpen,0);

  // Set position feedback control error gains
  // First parameter slotID - motor drive can support 4 different sets of PID values - we only need slot 0
  // Second parameter is PGain/IGain/DGain as applicable
  // Third parameter is timeout value - set to 0 for no checking
  // Note: Full-scale error output is 1023. I believe inputs to PID loop are encoder pulse counts.
  m_Motor->Config_kP(0, CLAW_PGAIN, 0);
  m_Motor->Config_kI(0, CLAW_IGAIN, 0);
  m_Motor->Config_kD(0, CLAW_DGAIN, 0);

  // set integration maximum accumulator value
  m_Motor->ConfigMaxIntegralAccumulator(0, CLAW_MAX_INTEGRAL_ACCUMULATOR, 0);

  // Set maximum allowed posotion controller closed loop error 
  m_Motor->ConfigAllowableClosedloopError(0, CLAW_ALLOWABLE_CLOSEDLOOP_ERROR, 0);

  // reset encoder
  ResetEncoderPosition();

  //disable safety feature
  m_Motor->SetSafetyEnabled(false);
}

// Set the default command for a subsystem here.
void Claw::InitDefaultCommand() { }



// ------------- Claw Functions -------------

void Claw::SetClawTargetPosition(int pos)
{
  // depending on position given to us, tell motor to turn to desired position (in # of pulse counts)
  switch (pos) {
    case 0:
      m_Motor->Set(ControlMode::Position, CLAW_BALL_POSITION);
      break;

    case 1:
      m_Motor->Set(ControlMode::Position, CLAW_OPEN_POSITION);
      break;

    case 2:
      m_Motor->Set(ControlMode::Position, CLAW_HATCH_POSITION);
      break;

    // otherwise do nothing - default case not req'd
  }
}



// Function returns true if Claw at, or near, its target position
bool Claw::IsClawAtTarget(void){
  
  if (abs(m_Motor->GetClosedLoopError()) <= CLAW_POSITION_TOLERANCE )
    return true;
  else
    return false;
}

// Function to return Claw position
// Returns 0 if Claw at bottom, 1 if in middle, 2 if at top
// Returns -1 if not in defined position 
int Claw::GetClawTargetPosition(void)
{  
  // by default, return -1 (Claw not at a specific position)
  int pos=-1;

  // get current Claw target
  int target = m_Motor->GetClosedLoopTarget(0);

   // depending on position given to us, tell motor to turn to desired position (in # of pulse counts)
  switch (target) {
  
    case CLAW_BALL_POSITION:
      pos = 0;
      break;

    case CLAW_OPEN_POSITION:
      pos = 1;
      break;

    case CLAW_HATCH_POSITION:
      pos = 2;
      break;
  }

  return (pos);
}



// initialize position control - to be called when subsystem has been re-homed
void Claw::InitPositionControl(){

  //reset encoder
  ResetEncoderPosition();
  
  //enable forward direction soft limit - set to maximum allowed encoder pulse counts at Claw top.
  m_Motor->ConfigForwardSoftLimitEnable(true,0);

  //enable reverse direction soft limit - assumes encoder pulse at bottom is 0
  m_Motor->ConfigReverseSoftLimitEnable(true, 0);
}

// initialize position control - to be called when subsystem has been re-homed
void Claw::InitForHoming(void){
  
  //enable forward direction soft limit - set to maximum allowed encoder pulse counts at Claw top.
  m_Motor->ConfigForwardSoftLimitEnable(false,0);

  //enable reverse direction soft limit - assumes encoder pulse at bottom is 0
  m_Motor->ConfigReverseSoftLimitEnable(false, 0);
}


// ------------- Encoder-Related Functions -------------


// Function to command Claw to move to a fixed position
// Input: Target position (in sensor units)
void Claw::SetClawTargetAnalog(int pos){

  // ensure position in valid range of drive
  if (pos<CLAW_SOFT_LIMIT_MIN )
      pos=CLAW_SOFT_LIMIT_MIN;
  if (pos>CLAW_SOFT_LIMIT_MAX)
      pos=CLAW_SOFT_LIMIT_MAX;

  // set motor target position
  m_Motor->Set(ControlMode::Position, pos);
}

// Function to get current Claw target position
// Output: Target position (in sensor units)
int Claw::GetClawTargetAnalog(void){
  return m_Motor->GetClosedLoopTarget(0);
}

// Resets Claw encoder position value
// USE ONLY WHEN Claw AT HOME POSITION (BOTTOM?)
void Claw::ResetEncoderPosition(void) {
  // first parameter - encoder position,
  m_Motor->SetSelectedSensorPosition(0);
}

// Returns Claw encoder position value (in raw sensor units)
int Claw::GetEncoderPosition(void) {  
  // return position of primary feedback sensor for PID loop ID (use 0)
  return m_Motor->GetSelectedSensorPosition(0);
}




// ------------- Motor Drive Functions -------------


// Directly set motor speed to be used for homing 
// Input: speed between -1 and 1
void Claw::SetClawMotorSpeed(float speed){
  m_Motor->Set(ControlMode::PercentOutput, speed);
}

// Check if limit switch is closed
bool Claw::IsFwdLimitSwitchClosed(void){
  return m_Motor->GetSensorCollection().IsFwdLimitSwitchClosed();
}

// Check if limit switch is closed
bool Claw::IsRevLimitSwitchClosed(void){
  return m_Motor->GetSensorCollection().IsRevLimitSwitchClosed();
}

// Returns motor drive current (amps)
float Claw::GetMotorCurrent(void) { 
  // return motor drive current
  return m_Motor->GetOutputCurrent();
}