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

    // determine type of target
    unsigned int targettype = Robot::m_Limelight.GetPipeline();

    // get target side lengths
    float vert = Robot::m_Limelight.GetVerticalSideLength();
    float hor = Robot::m_Limelight.GetHorizontalSideLength();

    // get target area of target (in sq pixels)
    float area = vert*hor;

    // average size of target - average of x and y lengths
    float avgsize = 0.5*(vert+hor) ;

    // aspect ratio of ball - check for devide-by-zero
    float aspect=0;
    if (vert !=0.0)
        aspect = hor / vert;
  
    // if we are targetting a ball
    //if (detected==true && targettype==1)
    //{
   
        // do we have a valid target? camera must detect target AND ball larger than minimum size AND ball rectangle must be ~square
        // if we are really close to ball, stop looking at aspect ratio
        // also check avg size, so we don't divide by zero!
        //if ( ((area >= 6000.0) || (area >= MIN_BALL_DETECTION_AREA) && (aspect > 0.5) && (aspect < 2.0)) && (avgsize!=0.0))
        //{
            // we have a valid target - populate target info
            target.Detected = true;
            target.TargetType = 1;
            target.Area = area;
            target.XAngle = Robot::m_Limelight.GetHorizontalTargetOffsetAngle();
            target.ZDistance = (36.0 / avgsize) * 93.0;
       // }
      
    //} // end if target is ball

    // return target data
    return target;
}


// Filtered Target Data
TARGET_DATA FilteredTarget;

// function to filter camera results
void FilterCameraChevronResults(void)
{
    static float FilteredDetection = 0.0;
    
    // Filter camera target detection
    FilteredDetection = 0.93 * FilteredDetection + 0.07*(Robot::m_Limelight.IsTargetPresent()); 
    FilteredTarget.Detected = (FilteredDetection >=0.75);

    // Target type - don't need filtering
    FilteredTarget.TargetType = Robot::m_Limelight.GetPipeline();

    // Filter camera XAngle
    FilteredTarget.XAngle = 0.99*FilteredTarget.XAngle + 0.01*Robot::m_Limelight.GetHorizontalTargetOffsetAngle();

    // Filter camtran vector
    Limelight::CamTran vector = Robot::m_Limelight.GetCameraTranslation(); 
    FilteredTarget.XDistance = 0.99*FilteredTarget.XDistance + 0.01*(-vector.x);
    FilteredTarget.ZDistance = 0.99*FilteredTarget.ZDistance + 0.01*(-vector.z);
}
