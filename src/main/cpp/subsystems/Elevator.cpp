/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "RobotMap.h"
#include "commands/ElevatorManualControl.h"

// Elevator constructor - this is run when elevator subysstem is first created
Elevator::Elevator() : Subsystem("Elevator") {

  // create individual motor control objects - assign unique CAN address to motor drive
  m_Motor1 = new WPI_TalonSRX(ELEVATOR_MOTOR1_CANID);
  m_Motor2 = new WPI_VictorSPX(ELEVATOR_MOTOR2_CANID);

  // set factory default settings
  m_Motor1->ConfigFactoryDefault();
  m_Motor2->ConfigFactoryDefault();

  // select quadrature encoder (first parameter) as primary feedback sensor (second parameter=0)
  // Third parameter kTimeoutMs is timeout to wait for Talon to confirm update - set to 0 for no checking
  m_Motor1->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);

  // sets direction of the encoder - set to true to invert phase (to change encoder direction)
  m_Motor1->SetSensorPhase(true);

  // set motor 2 to follow motor 1
  m_Motor2->Follow(*m_Motor1);

  // set nominal and peak outputs of drive 
  // nominal = 0, peak is +1 or -1 depending on direction
  // second parameter is timeout (use 0)
  m_Motor1->ConfigNominalOutputForward(0, 0);
  m_Motor1->ConfigNominalOutputReverse(0, 0);
  m_Motor1->ConfigPeakOutputForward (ELEVATOR_DRIVE_FULL_VLTG_FWD, 0);
  m_Motor1->ConfigPeakOutputReverse (-ELEVATOR_DRIVE_FULL_VLTG_REV, 0);

  // Set elevator motor maximum current level
  m_Motor1->ConfigContinuousCurrentLimit(ELEVATOR_CURRENT_LIMIT);
  m_Motor1->EnableCurrentLimit(true);

  // set up forward direction soft (software) limit - set to maximum allowed encoder pulse counts at elevator top
  m_Motor1->ConfigForwardSoftLimitEnable(true,0);
  m_Motor1->ConfigForwardSoftLimitThreshold(ELEVATOR_SOFT_LIMIT_MAX);
  
  // set up reverse direction soft limit - assumes encoder pulse at bottom is 0
  m_Motor1->ConfigReverseSoftLimitEnable(true, 0);
  m_Motor1->ConfigReverseSoftLimitThreshold(ELEVATOR_SOFT_LIMIT_MIN);

  // configure limit switches
	m_Motor1->ConfigReverseLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_FeedbackConnector,LimitSwitchNormal::LimitSwitchNormal_NormallyOpen,0);

  // set motor ramp rate (from neutral to full) used to avoid sudden changes in speed
  //m_Motor1-> ConfigClosedloopRamp(ELEVATOR_DRIVE_MAXRAMP, 0);

  // Set position feedback control error gains
  // First parameter slotID - motor drive can support 4 different sets of PID values - we only need slot 0
  // Second parameter is PGain/IGain/DGain as applicable
  // Third parameter is timeout value - set to 0 for no checking
  // Note: Full-scale error output is 1023. I believe inputs to PID loop are encoder pulse counts.
  m_Motor1->Config_kP(0, ELEVATOR_PGAIN, 0);
  m_Motor1->Config_kI(0, ELEVATOR_IGAIN, 0);
  m_Motor1->Config_kD(0, ELEVATOR_DGAIN, 0);

  // set integration maximum accumulator value
  m_Motor1->ConfigMaxIntegralAccumulator(0, ELEVATOR_MAX_INTEGRAL_ACCUMULATOR, 0);
  
  // Set maximum allowed posotion controller closed loop error
  // within this error, no control action is performed (i.e control deadband)
  m_Motor1->ConfigAllowableClosedloopError(0, ELEVATOR_ALLOWABLE_CLOSEDLOOP_ERROR, 0);

  // reset encoder
  ResetEncoderPosition();

  // disable safety feature
  m_Motor1->SetSafetyEnabled(false);
  m_Motor2->SetSafetyEnabled(false);
}

// default command to run with the subsystem
void Elevator::InitDefaultCommand() {
  SetDefaultCommand(new ElevatorManualControl());
}



// ------------- Elevator Functions -------------


// Function to command elevator to move to a fixed position
// Input: position number. If not valid position, do nothing
void Elevator::SetElevatorPresetPosition(int pos)
{
  // depending on position given to us, tell motor to turn to desired position (in # of pulse counts)
  switch (pos) {
    case 0:
      m_Motor1->Set(ControlMode::Position, ELEVATOR_POSITION0);
      break;

    case 1:
      m_Motor1->Set(ControlMode::Position, ELEVATOR_POSITION1);
      break;

    case 2:
      m_Motor1->Set(ControlMode::Position, ELEVATOR_POSITION2);
      break;

    case 3:
      m_Motor1->Set(ControlMode::Position, ELEVATOR_POSITION3);
      break;

    case 4:
      m_Motor1->Set(ControlMode::Position, ELEVATOR_POSITION4);
      break;

    case 5:
      m_Motor1->Set(ControlMode::Position, ELEVATOR_POSITION5);
      break;

    // otherwise do nothing - default case not req'd
  }
}


// Function to return elevator position
// Returns 0 if elevator at bottom, 1 if in middle, 2 if at top
// Returns -1 if not in defined position 
int Elevator::GetElevatorTargetPresetPosition(void)
{  
  // by default, return -1 (elevator not at a specific position)
  int pos=-1;

  // get current elevator target
  int target = m_Motor1->GetClosedLoopTarget(0);

   // depending on position given to us, tell motor to turn to desired position (in # of pulse counts)
  switch (target) {
  
    case ELEVATOR_POSITION0:
      pos = 0;
      break;

    case ELEVATOR_POSITION1:
      pos = 1;
      break;

    case ELEVATOR_POSITION2:
      pos = 2;
      break;

    case ELEVATOR_POSITION3:
      pos = 3;
      break;

    case ELEVATOR_POSITION4:
      pos = 4;
      break;

    case ELEVATOR_POSITION5:
      pos= 5;
      break;
  }

  return (pos);
} 

// Function to return elevator's next preset position (next higher position)
int Elevator::GetElevatorNextHigherPresetPosition(void) {

  // get current elevator position
  //int position = m_Motor1->GetSelectedSensorPosition(0);
  int position = m_Motor1->GetClosedLoopTarget(0);
  // next position
  int next = 0;

  if (position >= (ELEVATOR_POSITION0-ELEVATOR_POSITION_TOLERANCE))
    next = 1;
  if (position >= (ELEVATOR_POSITION1-ELEVATOR_POSITION_TOLERANCE))
    next = 2;
  if (position >= (ELEVATOR_POSITION2-ELEVATOR_POSITION_TOLERANCE))
    next = 3;
  if (position >= (ELEVATOR_POSITION3-ELEVATOR_POSITION_TOLERANCE))
    next = 4;
  if (position >= (ELEVATOR_POSITION4-ELEVATOR_POSITION_TOLERANCE))
    next = 5;
  
  // return next elevator position
  return next;
  }

// Function to return elevator's next preset position (next higher position)
int Elevator::GetElevatorNextLowerPresetPosition(void) {

  // get current elevator position
  //int position = m_Motor1->GetSelectedSensorPosition(0);
  int position = m_Motor1->GetClosedLoopTarget(0);
  
  // next position
  int next = 0;

  if (position <= (ELEVATOR_POSITION5+ELEVATOR_POSITION_TOLERANCE))
    next = 4;
  if (position <= (ELEVATOR_POSITION4+ELEVATOR_POSITION_TOLERANCE))
    next = 3;
  if (position <= (ELEVATOR_POSITION3+ELEVATOR_POSITION_TOLERANCE))
    next = 2;
  if (position <= (ELEVATOR_POSITION2+ELEVATOR_POSITION_TOLERANCE))
    next = 1;
  if (position <= (ELEVATOR_POSITION1+ELEVATOR_POSITION_TOLERANCE))
    next = 0;
  
  // return next elevator position
  return next;
  }



// Function returns true if elevator at, or near, its target position
bool Elevator::IsElevatorAtTarget(void)
{
  if (abs(m_Motor1->GetClosedLoopError()) <= ELEVATOR_POSITION_TOLERANCE )
    return true;
  else
    return false;
}




// ------------- Encoder-Related Functions -------------


// Function to command elevator to move to a fixed position
// Input: Target position (in sensor units)
void Elevator::SetElevatorTargetAnalog(int pos){

  // ensure position in valid range of drive
  if (pos<ELEVATOR_SOFT_LIMIT_MIN )
      pos=ELEVATOR_SOFT_LIMIT_MIN;
  if (pos>ELEVATOR_SOFT_LIMIT_MAX)
      pos=ELEVATOR_SOFT_LIMIT_MAX;

  // set motor target position
  m_Motor1->Set(ControlMode::Position, pos);
}

// Function to get current elevator target position
// Output: Target position (in sensor units)
int Elevator::GetElevatorTargetAnalog(void){
  return m_Motor1->GetClosedLoopTarget(0);
}

// Resets elevator encoder position value
// USE ONLY WHEN ELEVATOR AT HOME POSITION (BOTTOM?)
void Elevator::ResetEncoderPosition(void)
{
  // first parameter - encoder position, second parameter PID loop ID (use 0), third is timeout (use 0)
  m_Motor1->SetSelectedSensorPosition(0, 0, 0);
}

// Returns elevator encoder position value (in raw sensor units)
int Elevator::GetEncoderPosition(void)
{  
  // return position of primary feedback sensor for PID loop ID (use 0)
  return m_Motor1->GetSelectedSensorPosition(0);
}

// Returns elevator encoder speed value (in raw sensor units per 100ms)
int Elevator::GetEncoderSpeed(void)
{
  // return speed of primary feedback sensor for PID loop ID (use 0)
  return m_Motor1->GetSelectedSensorVelocity(0);
}

// ------------- Motor Drive Functions -------------

// Returns motor drive current (amps)
float Elevator::GetMotorCurrent(void)
{ 
  return m_Motor1->GetOutputCurrent();
}

// Check if limit switch is closed
bool Elevator::IsFwdLimitSwitchClosed(void){
  return m_Motor1->GetSensorCollection().IsFwdLimitSwitchClosed();
}

// Check if limit switch is closed
bool Elevator::IsRevLimitSwitchClosed(void){
  return m_Motor1->GetSensorCollection().IsRevLimitSwitchClosed();
}


// ------------- Shuffleboard Functions -------------

void Elevator::InitializeShuffleBoard(void)
{
    // Main Tab
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Elevator");

    MotorEncoder=Tab->Add("Encoder", 0.0).GetEntry();
    MotorTarget=Tab->Add("Target", 0.0).GetEntry();
    MotorCurrent=Tab->Add("Current", 0.0).GetEntry();
}

// update shuffle board with current drive values
void Elevator::UpdateShuffleBoard(void) {

  MotorEncoder.SetDouble(GetEncoderPosition());
  MotorTarget.SetDouble(GetElevatorTargetAnalog());
  MotorCurrent.SetDouble(GetMotorCurrent());
}


