// Target detection and estimation functions
// These functions may use various robot systems as required 

#include "detection/TargetDetection.h"


// ---------- Target Detection Routines ----------


// Test Data from Lab (Feb 3/18 estimates - requires retest for better accuracy)
// Size (typ x and y)            Distance              
// 84                            42" (1.1m)
// 36                            93" (2.4m)  (base case)
// 16                            168" (4.3m)

TARGET_DATA GetTargetEstimation(void)
{
    TARGET_DATA target;

    // assume no target detected unless proven otherwise
    target.Detected = false;
    
    // determine if camera has acquired a target
    bool detected = Robot::m_Limelight.IsTargetPresent();

    // get target side lengths
    float vert = Robot::m_Limelight.GetVerticalSideLength();
    float hor = Robot::m_Limelight.GetHorizontalSideLength();

    // get target area of target (in sq pixels)
    float area = vert*hor;

  
    if (detected==true && area > MIN_HEX_DETECTION_AREA && vert > MIN_HEX_VERT_SIZE)
    {
        target.Detected = true;
        target.TargetType = 0;
        target.Area = area;
        target.XAngle = Robot::m_Limelight.GetHorizontalTargetOffsetAngle();
        target.ZDistance = (235.0 / vert);
    }

    // return target data
    return target;
}
