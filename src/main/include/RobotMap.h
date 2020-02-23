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


// ------------- Camera Tilt Constants


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
#define WRIST_MOTOR_CANID               13


//----------UPLIFTER CONSTANTS----------------
#define UPLIFTER_MOTOR_CANID              12