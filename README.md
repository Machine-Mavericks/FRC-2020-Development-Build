# FRC-2020-Development-Build
FRC 7480's code for Infinite Recharge

Development build of Machine Mavericks robot control system using 2020 FRC libraries

Repository includes source (src) files folder. Copy 'src' folder into main robot project folder and rebuild project Requires: 2020 FRC Studio and WPI libraries, and Victor SPX libraries installed.fs

Jan 27/2019: Rev 1 Now includes fully functional tank and arcade drive modes - both only available when robot is in teleop mode Tank mode is default. Press and hold right joystick trigger for arcade drive mode. Releasing trigger returns robot to tank mode. Right joystick throttle controls thrust throttle for both Tank and Arcade modes. Subsystems include MainDrive (incl left/right encoders) and NavX for Gyro monitoring (not used in this release) Commands include TankDrive and ArcadeDrive Constants now in Robotmap.h All driver station updates moved to DriverStation.h

Known issues:
in arcade.cpp the line about m_defaultTeleOp won't compile if it's not commented out

May require fine-tuning of joystick response characteristics which can be done at later date
For next release:


Tank drive joystick drive requires dead-zone and adjustment to joystick response characteristics for more precise low-speed driving
