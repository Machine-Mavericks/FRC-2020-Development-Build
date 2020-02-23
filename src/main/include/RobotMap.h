/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once



// ------------- General -------------

// Joystick port Ids
#define DRIVE_JOYSTICK_PORT             0
#define MECHANISM_CONTROLLER_PORT       2

// Joystick Axis IDs
#define LEFT_JOYSTICK_X_AXIS_ID         0
#define LEFT_JOYSTICK_Y_AXIS_ID         1
#define RIGHT_JOYSTICK_X_AXIS_ID        4 
#define RIGHT_JOYSTICK_Y_AXIS_ID        5 
#define LEFT_TRIGGER_AXIS_ID            2
#define RIGHT_TRIGGER_AXIS_ID           3


// Other constants
constexpr double kPi = 3.14159265358979;
constexpr double degToRad = 0.01745328;

// ------------- Main Drive Constants -------------


// Drive Type
// Uncomment type of drive to be used. Comment out rest
#define DRIVE2020
//#define DRIVE2019

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

// RangeFinder sensor IDS - DEFINES RoboRio I/O # for ultrasonic sensor connections

#define RANGEFINDER_PING_CHANNEL         9
#define RANGEFINDER_ECHO_CHANNEL         8

// Throttle Curve Coefficients - used for tank and arcade drive modes
#define LINEAR_WEIGHT                   1.0                     // value between 0 and 1
#define CUBIC_WEIGHT                    (1.0 - LINEAR_WEIGHT)   // automatically calculated to ensure summing to 1

// Robot wheel diameter (in inches) - used to determine travel distance
#define WHEEL_DIAMETER                  6.0      

// Robot encocer resolution (pulse counts per revolution)
#define ENCODER_PULSE_PER_REVOLUTION    360.0


// ------------- Camera Wrist Constants


// camera servo digital I/O channel
#define CAMERA_SERVO_ID                 0

// ------------- Ultrasonic Constants
// ultrasonic ping/echo channels
#define ULTRASONIC_PORT                 0

// ------------- Wheel of Fortune Constants
#define WOF_MOTOR_CANID                 8
#define WOF_WHEEL_DIAMETER              3.0



//----------- Climb Constants----------
#define CLIMB_MOTOR_CANID               10


//--------Shooter Constants
#define SHOOTER_2_MOTOR_CANID           6
#define SHOOTER_1_MOTOR_CANID           7

//------LED CONSTANTS----------------------
#define LED_PORT                        3

//----------INTAKE CONSTANTS----------------
#define INTAKE_MOTOR_CANID              9

// Elevator positional tolerance. Elevator reports to driverstation if position if within +/- tolerance of target position
#define INTAKE_TILT_POSITION_TOLERANCE         100

#define INTAKE_TILT_MAX_INTEGRAL_ACCUMULATOR   10000  // Feb 18 2000

//----------UPLIFTER CONSTANTS----------------
#define UPLIFTER_MOTOR_CANID              12

//-------- INTAKE TILT CONSTANTS--------------
#define INTAKE_TILT_MOTOR_CANID               13

// Motor encoder counts per revolution
// TalonSRX uses 4x count mode - encocer normally has 1024 pulses per revolution
#define INTAKE_TILT_ENCODER_PULSE_PER_REVOLUTION   4096

    // Maximum applied motor voltage in forward and reverse direction (can be used to limit speed)
    // Value betwen 0.0 and 1.0
    #define INTAKE_TILT_DRIVE_FULL_VLTG_FWD        0.5
    #define INTAKE_TILT_DRIVE_FULL_VLTG_REV        0.5
    
    // motor current limit
    #define INTAKE_TILT_CURRENT_LIMIT              6
    #define INTAKE_TILT_PEAKCURRENT_LIMIT          8
    #define INTAKE_TILT_PEAKCURRENT_TIME           2

    // Wrist position control error gains
    #define INTAKE_TILT_PGAIN                      1
    #define INTAKE_TILT_IGAIN                      0.0004
    #define INTAKE_TILT_DGAIN                      80   


// Maximum closed loop error (in sensor units)
#define INTAKE_TILT_ALLOWABLE_CLOSEDLOOP_ERROR 1

// Elevator soft (software) limits - in # of encoder pulses
// MiN would normally be 0 for elevator, corresponding to lowest position (home position)
#define INTAKE_TILT_SOFT_LIMIT_MIN             0  
#define INTAKE_TILT_SOFT_LIMIT_MAX             1100
         
// Elevator defined positions - in # of encoder pulses
#define INTAKE_TILT_UP_POSITION                -50  //0 for claw
#define INTAKE_TILT_MID_POSITION               515
#define INTAKE_TILT_DOWN_POSITION              1000 // 1030  
#define INTAKE_TILT_BALL_POSITION              1060 // 1060