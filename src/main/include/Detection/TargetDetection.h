// Target detection and estimation functions
// These functions may use various robot systems as required 

#pragma once

#include "robot.h"

// minimum ball detection area (# square pixels)
// 1000 sq pixels corresponds to ~8 ft
#define MIN_BALL_DETECTION_AREA     750.0

// minimum chevron detection area (# square pixels)
// 500 sq pixels corresponds to TBD ft
#define MIN_CHEVRON_DETECTION_AREA 1.0

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

void FilterCameraChevronResults(void);