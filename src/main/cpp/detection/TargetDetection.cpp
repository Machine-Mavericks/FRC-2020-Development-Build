// Target detection and estimation functions
// These functions may use various robot systems as required 

#include "detection/TargetDetection.h"
#include <frc/Shuffleboard/Shuffleboard.h>

// ---------- Target Detection Routines ----------

// Ball Test Data from Lab (Feb 3/18 estimates - requires retest for better accuracy)
// Size (typ x and y)            Distance              
// 84                            42" (1.1m)
// 36                            93" (2.4m)  (base case)
// 16                            168" (4.3m)

// Chevron Test Data from Lab (Feb 16/19 estimates)
// Avg Size (=1/2*(x+y))        Distance            Size*Distance
// 182                          42.5"               7,735       
// 127                          61.5"               7,810
// 104                          72"                 7,490
// 85                           96.5"               8,202
// 59                           140"                8,260



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
    if (detected==true && targettype==1)
    {
   
        // do we have a valid target? camera must detect target AND ball larger than minimum size AND ball rectangle must be ~square
        // if we are really close to ball, stop looking at aspect ratio
        // also check avg size, so we don't divide by zero!
        if ( ((area >= 6000.0) || (area >= MIN_BALL_DETECTION_AREA) && (aspect > 0.5) && (aspect < 2.0)) && 
            (avgsize!=0.0))
        {
            // we have a valid target - populate target info
            target.Detected = true;
            target.TargetType = 1;
            target.Area = area;
            target.XAngle = Robot::m_Limelight.GetHorizontalTargetOffsetAngle();
            target.ZDistance = (36.0 / avgsize) * 93.0;
        }
      
    } // end if target is ball

    // if we are targetting a chevron
    else if (detected==true && (targettype==0 || targettype==2 || targettype==3))
    {

       // do we have a valid target? camera must detect target AND ball larger than minimum size AND ball rectangle must be ~square
        // if we are really close to ball, stop looking at aspect ratio
        // also check avg size, so we don't divide by zero!
        if (area >= MIN_CHEVRON_DETECTION_AREA)
        {
            // we have a valid target - populate target info
            target.Detected = true;
            target.TargetType = 0;
            target.Area = area;
            target.XAngle = Robot::m_Limelight.GetHorizontalTargetOffsetAngle();
            
            // get camtran vector from camera
            Limelight::CamTran vector = Robot::m_Limelight.GetCameraTranslation();
            target.XDistance = vector.x;
            if (avgsize!=0.0) 
                target.ZDistance = 7900.0 / avgsize; 
            else
                target.ZDistance = 0.0;
                 
        }
    } // end if target is chevron

    // return target data
    return target;
}


// ------------- Shuffleboard Functions -------------

nt::NetworkTableEntry BallDetected, ChevronDetected;
nt::NetworkTableEntry ZDistance, XDistance, XAngle, Area;


// update shuffle board with current target values
void TargetDetectionInitializeShuffleBoard(void)
{
    ShuffleboardTab *Tab = &Shuffleboard::GetTab("Target Detection");

    BallDetected = Tab->Add("Ball Detected", false).GetEntry();
    ChevronDetected = Tab->Add("Chevron Detected", false).GetEntry();
    
    ShuffleboardLayout *l1 = &Tab->GetLayout("Target", BuiltInLayouts::kList);
    l1->WithPosition(2,0);
    l1->WithSize(1,4);
    ZDistance = l1->Add("ZDistance", 0.0).GetEntry();
    XDistance = l1->Add("XDistance", 0.0).GetEntry();
    XAngle = l1->Add("XAngle", 0.0).GetEntry();
    Area = l1->Add("Area", 0.0).GetEntry();
}

// update shuffle board with current target values
void TargetDetectionUpdateShuffleBoard(void)
{
    TARGET_DATA target = GetTargetEstimation();
    
    BallDetected.SetBoolean(target.Detected&&target.TargetType==1);
    ChevronDetected.SetBoolean(target.Detected&&target.TargetType==0);
    
    ZDistance.SetDouble(target.ZDistance);
    XDistance.SetDouble(target.XDistance);
    XAngle.SetDouble(target.XAngle);
    Area.SetDouble(target.Area);
}
