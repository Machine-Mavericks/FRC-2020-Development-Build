// Target detection and estimation functions
// These functions may use various robot systems as required 

#pragma once

#include "robot.h"

// minimum chevron detection area (# square pixels)
#define MIN_HEX_DETECTION_AREA  1000.0
#define MIN_HEX_VERT_SIZE       20.0

struct TARGET_DATA {
    bool Detected;              // true if target has been detected
    unsigned int TargetType;    // type of target (0=chevron, 1=ball)
    float Area;                 // area of detected target (in # sq pixels)
    float XAngle;               // angle (deg) of target relative to center-line of camera
    float XDistance;            // estimated x distance (in) of target from camera (chevron only)
    float ZDistance;            // estimated z distance (in) of target from camera
    TARGET_DATA()               // defaults
    { Detected = false; }
};

// ---------- Target Detection Routines ----------

// returns ball target data
TARGET_DATA GetTargetEstimation(void);
