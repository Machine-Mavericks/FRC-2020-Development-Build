/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Limight subsytem contains all functions needed to access camera

#pragma once

#include <frc/commands/Subsystem.h>
#include <networkTables/networkTable.h>
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include <frc/Shuffleboard/Shuffleboard.h>

using namespace frc;

class Limelight : public frc::Subsystem {
    public:
  
    // constructor - used to initialize specific hardware
    Limelight();

    // default command to run with the subsystem
    void InitDefaultCommand() override;
  

    // ---------- Camera Control Functions

    // set/get Limelight camera's current pipeline
    void SetPipeline(unsigned int num);
    unsigned int GetPipeline(void);


    // ---------- Camera Data Functions
    
    // get angles to center of target
    float GetHorizontalTargetOffsetAngle();
    float GetVerticalTargetOffsetAngle();
    float GetTargetSkew();
 
    // get camera translation vector to target
    // limelight camera translation vector definition
    struct CamTran {
        float x;
        float y;
        float z;
        float pitch;
        float yaw;
        float roll;
        CamTran() {x=0.0; y=0.0; z=0.0; pitch=0.0; yaw=0.0; roll=0.0; }
    };
    Limelight::CamTran GetCameraTranslation(); 
 
    // get target detection time latency
    float GetLatencyContribution();

    // get whether target is currently detected or not
    bool IsTargetPresent();

    // get target atributes
    float GetTargetArea();
    int GetShortestSide();
    int GetLongestSide();
    int GetHorizontalSideLength();
    int GetVerticalSideLength();
 
    // these are the raw contours from Limelight
    float GetRawScreenspaceX0();
    float GetRawScreenspaceX1();
    float GetRawScreenspaceX2();
    float GetRawScreenspaceY0();
    float GetRawScreenspaceY1();
    float GetRawScreenspaceY2();
    float GetRawArea0();
    float GetRawArea1();
    float GetRawArea2();
    float GetRawSkew0();
    float GetRawSkew1();
    float GetRawSkew2();

    // update shuffle board with current values
    void InitializeShuffleBoard();
    void UpdateShuffleBoard();

    private:

    // create pointer to Limelight object
    std::shared_ptr<NetworkTable> table;

    // Shubbleboard Controls
    nt::NetworkTableEntry Pipeline, TargetPresent;
    nt::NetworkTableEntry AngleX, AngleY, Skew;
    nt::NetworkTableEntry Area, Short, Long, Hor, Vert;
    nt::NetworkTableEntry X, Y, Z, Pitch, Yaw, Roll;
};


