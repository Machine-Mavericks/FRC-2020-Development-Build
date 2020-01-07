/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

// ------------- Robot Type -------------

// comment out any that do NOT match robot type
// NOTE: NO MORE THAN ONE TYPE CAN BE DEFINED AT ANY ONE TIME

#define ROBOTTYPE_CLAW
//#define ROBOTTYPE_SNOWBLOWER


// ------------- General -------------

// Joystick port Ids
#define LEFT_JOYSTICK_PORT              0
#define RIGHT_JOYSTICK_PORT             1
#define MECHANISM_CONTROLLER_PORT       2

// Joystick Axis IDs
#define JOYSTICK_X_AXIS_ID              0
#define JOYSTICK_Y_AXIS_ID              1
#define JOYSTICK_THROTTLE_AXIS_ID       3

// Other constants
constexpr double kPi = 3.14159265358979;

// ------------- Main Drive Constants -------------

// Motor Drive CANbus node IDs
#define FRONT_LEFT_MOTOR_CANID          2
#define FRONT_RIGHT_MOTOR_CANID         3
#define REAR_LEFT_MOTOR_CANID           5
#define REAR_RIGHT_MOTOR_CANID          4

// Encoder Channel IDs - defines RoboRio I/O # for each encoder channel 
#define RIGHT_ENCODER_CHANNELA_ID       2       
#define RIGHT_ENCODER_CHANNELB_ID       3
#define LEFT_ENCODER_CHANNELA_ID        0
#define LEFT_ENCODER_CHANNELB_ID        1

// Throttle Curve Coefficients - used for tank and arcade drive modes
#define LINEAR_WEIGHT                   1.0                     // value between 0 and 1
#define CUBIC_WEIGHT                    (1.0 - LINEAR_WEIGHT)   // automatically calculated to ensure summing to 1

// Robot wheel diameter (in inches) - used to determine travel distance
#define WHEEL_DIAMETER                  6.0      

// Robot encocer resolution (pulse counts per revolution)
#define ENCODER_PULSE_PER_REVOLUTION    360.0


// ------------- Camera Tilt Constants


// camera servo digital I/O channel
#define CAMERA_SERVO_ID                 0

// camera tilt servo angles (in deg)
#define CAMERA_TILTANGLE_BALL           130.0  
#define CAMERA_TILTANGLE_CHEVRON        100.0 

// ------------- Elevator Constants -------------

// Motor Drive CANbus node IDs
#define ELEVATOR_MOTOR1_CANID           6
#define ELEVATOR_MOTOR2_CANID           7

// Joystick Axis IDs
#define JOYSTICK_ELEVATOR_AXIS_ID       5

// Motor encoder counts per revolution
// TalonSRX uses 4x count mode - encocer normally has 1024 pulses per revolution
#define ELEVATOR_ENCODER_PULSE_PER_REVOLUTION   4096

// Maximum ramp rate of drive - time(s) from zero to full appplied voltage
#define ELEVATOR_DRIVE_MAXRAMP          0.15

// Maximum applied motor voltage in forward and reverse direction (can be used to limit speed)
// Value betwen 0.0 and 1.0
#define ELEVATOR_DRIVE_FULL_VLTG_FWD    1.0
#define ELEVATOR_DRIVE_FULL_VLTG_REV    1.0

// motor current limit
#define ELEVATOR_CURRENT_LIMIT          10

// Elevator position control error gains
#define ELEVATOR_PGAIN                  0.5
#define ELEVATOR_IGAIN                  0.003 // was 0.004 Mar 3/19   
#define ELEVATOR_DGAIN                  20.0        
#define ELEVATOR_MAX_INTEGRAL_ACCUMULATOR   40000.0     // in encoder units x ms

// Maximum closed loop error - within this error no control action is performed (in sensor units)
#define ELEVATOR_ALLOWABLE_CLOSEDLOOP_ERROR 1

// Elevator soft (software) limits - in # of encoder pulses
// Min would normally be 0 for elevator, corresponding to lowest position (home position)
#define ELEVATOR_SOFT_LIMIT_MIN         0  
#define ELEVATOR_SOFT_LIMIT_MAX         67000

// Elevator defined positions - in # of encoder pulses
#ifdef ROBOTTYPE_CLAW
#define ELEVATOR_POSITION0              0       //Bottom
#define ELEVATOR_POSITION1              7300     //Lowest Ball Rocket
#define ELEVATOR_POSITION2              12530   //Lowest Hatch
#define ELEVATOR_POSITION3              38300   //Medium Ball Rocket
#define ELEVATOR_POSITION4              43600   //Medium Hatch Rocket
#define ELEVATOR_POSITION5              67000   //Highest Possible Height
#endif
#ifdef ROBOTTYPE_SNOWBLOWER
#define ELEVATOR_POSITION0              0
#define ELEVATOR_POSITION1              3600
#define ELEVATOR_POSITION2              4825
#define ELEVATOR_POSITION3              35360
#define ELEVATOR_POSITION4              40000
#define ELEVATOR_POSITION5              67000
#endif
// Elevator positional tolerance. Elevator reports to driverstation if position if within +/- tolerance of target position
#define ELEVATOR_POSITION_TOLERANCE     200


// ------------- IntakeTilt Constants -------------


// Motor Drive CANbus node IDs
#define TILT_MOTOR_CANID                8

// Motor encoder counts per revolution
// TalonSRX uses 4x count mode - encocer normally has 1024 pulses per revolution
#define TILT_ENCODER_PULSE_PER_REVOLUTION   4096

#ifdef ROBOTTYPE_CLAW
    // Maximum applied motor voltage in forward and reverse direction (can be used to limit speed)
    // Value betwen 0.0 and 1.0
    #define TILT_DRIVE_FULL_VLTG_FWD        0.50   // 0.25 Feb 17
    #define TILT_DRIVE_FULL_VLTG_REV        0.50
    
    // motor current limit
    #define TILT_CURRENT_LIMIT              5
    #define TILT_PEAKCURRENT_LIMIT          8
    #define TILT_PEAKCURRENT_TIME           1

    // Tilt position control error gains
    #define TILT_PGAIN                      6.8  // 8.5 unstable// 3.0 Feb 23    // 1.0 Feb 18 2019
    #define TILT_IGAIN                      0.02  // 0.02: div 10 Feb 17
    #define TILT_DGAIN                      350.0 // 250.0 // 0.327   // 0.1   
#endif

#ifdef ROBOTTYPE_SNOWBLOWER
    // Maximum applied motor voltage in forward and reverse direction (can be used to limit speed)
    // Value betwen 0.0 and 1.0
    #define TILT_DRIVE_FULL_VLTG_FWD        0.5
    #define TILT_DRIVE_FULL_VLTG_REV        0.5
    
    // motor current limit
    #define TILT_CURRENT_LIMIT              6
    #define TILT_PEAKCURRENT_LIMIT          8
    #define TILT_PEAKCURRENT_TIME           2

    // Tilt position control error gains
    #define TILT_PGAIN                      1
    #define TILT_IGAIN                      0.0004
    #define TILT_DGAIN                      80   
#endif


// Maximum closed loop error (in sensor units)
#define TILT_ALLOWABLE_CLOSEDLOOP_ERROR 1

// Elevator soft (software) limits - in # of encoder pulses
// MiN would normally be 0 for elevator, corresponding to lowest position (home position)
#define TILT_SOFT_LIMIT_MIN             0  
#define TILT_SOFT_LIMIT_MAX             1100
         
// Elevator defined positions - in # of encoder pulses
#define TILT_UP_POSITION                -50  //0 for claw
#define TILT_MID_POSITION               515
#define TILT_DOWN_POSITION              1000 // 1030  
#define TILT_BALL_POSITION              1060 // 1060

// Elevator positional tolerance. Elevator reports to driverstation if position if within +/- tolerance of target position
#define TILT_POSITION_TOLERANCE         100

#define TILT_MAX_INTEGRAL_ACCUMULATOR   10000  // Feb 18 2000



// ------------- Claw Constants -------------


// Motor Drive CANbus node IDs
#ifdef ROBOTTYPE_CLAW
    #define CLAW_MOTOR_CANID                9
#else
    #define CLAW_MOTOR_CANID                20
#endif

// Motor encoder counts per revolution
// TalonSRX uses 4x count mode - encocer normally has 1024 pulses per revolution
#define CLAW_ENCODER_PULSE_PER_REVOLUTION   4096

// Maximum applied motor voltage in forward and reverse direction (can be used to limit speed)
// Value betwen 0.0 and 1.0
#define CLAW_DRIVE_FULL_VLTG_FWD        1.0
#define CLAW_DRIVE_FULL_VLTG_REV        1.0

// claw current limit (A)
#define CLAW_CURRENT_LIMIT              1

// Elevator soft (software) limits - in # of encoder pulses
// MiN would normally be 0 for elevator, corresponding to lowest position (home position)
#define CLAW_SOFT_LIMIT_MIN             0  
#define CLAW_SOFT_LIMIT_MAX             1000
         
// Elevator defined positions - in # of encoder pulses
#define CLAW_BALL_POSITION              1000
#define CLAW_OPEN_POSITION              110 
#define CLAW_HATCH_POSITION             515

// Elevator position control error gains
#define CLAW_PGAIN                      50.0   // Feb 18 20.0
#define CLAW_IGAIN                      0.02  // Feb 18 0.001
#define CLAW_DGAIN                      0.01         

// Maximum closed loop error (in sensor units)
#define CLAW_ALLOWABLE_CLOSEDLOOP_ERROR 10

#define CLAW_POSITION_TOLERANCE         50

#define CLAW_MAX_INTEGRAL_ACCUMULATOR   2000


// ------------- Snowblower Constants -------------


// Motor Drive CANbus node IDs
#ifdef ROBOTTYPE_SNOWBLOWER
    #define SNOWBLOWER_MOTOR_CANID          9
#else
    #define SNOWBLOWER_MOTOR_CANID          20
#endif

// claw current limit (A)
#define SNOWBLOWER_CURRENT_LIMIT_IN     4
#define SNOWBLOWER_CURRENT_LIMIT_OUT    5


// --------- LobClaw constants ---------------------------------------------------------

#define LC_OPEN_CHANNEL 1
#define LC_CLOSE_CHANNEL 2

//-------------- Indicator Light constants--------------
#define LIGHT_CHANNEL 4