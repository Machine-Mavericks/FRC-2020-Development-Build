/****************************************************************************
    Description:	Defines the Poses used for autonomous.
    Classes:		CTrajectoryConstants
    Project:		2020 Infinite Recharge Robot Code.
    Copyright 2020 First Team 3284 - Camdenton LASER Robotics.
****************************************************************************/
#ifndef TrajectoryConstants_h
#define TrajectoryConstants_h

#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/Trajectory.h>

using namespace frc;
using namespace units;
using namespace std;
/////////////////////////////////////////////////////////////////////////////

class CTrajectoryConstants
{
public:

enum TrajectoryList {   Straight05m,
                        Straight10m,
                        Straight125m,
                        Straight15m,
                        Straight20m,
                        Straight25m,
                        Straight30m,
                        RevStraight05m,
                        RevStraight10m,
                        RevStraight15m,
                        RevStraight20m,
                        RevStraight25m,
                        SCurve2,
                        SCurve,
                        TrenchtoShoot,
                        TrenchtoBay,
                        aTrenchtoShoot};

    void SelectTrajectory(TrajectoryList nTrajectory)
    {
        // Retrieve the correct trajectory.
        switch(nTrajectory)
        {
            case Straight05m:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { 0.15_m, 0.0_m },
                    Translation2d { 0.30_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  0.50_m, 0.0_m, Rotation2d(0_deg) };
            break;
            

            case Straight10m:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { 0.35_m, 0.0_m },
                    Translation2d { 0.7_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  1.0_m,	0.0_m, Rotation2d(0_deg) };
            break;

            case Straight125m:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { 0.35_m, 0.0_m },
                    Translation2d { 0.7_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  1.25_m,	0.0_m, Rotation2d(0_deg) };
            break;


            case Straight15m:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { 0.5_m, 0.0_m },
                    Translation2d { 1.0_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  1.50_m,	0.0_m, Rotation2d(0_deg) };
            break;
            
            
            case Straight20m:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { 0.7_m, 0.0_m },
                    Translation2d { 1.4_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  2.00_m,	0.0_m, Rotation2d(0_deg) };
            break;
            
            
            case Straight25m:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { 0.8_m, 0.0_m },
                    Translation2d { 1.6_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  2.50_m,	0.0_m, Rotation2d(0_deg) };
            break;

            case Straight30m:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { 1.0_m, 0.0_m },
                    Translation2d { 2.0_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  3.00_m,	0.0_m, Rotation2d(0_deg) };
            break;
            

            // --------------- REVERSE PATHS



            case RevStraight05m:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { -0.15_m, 0.0_m },
                    Translation2d { -0.30_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  -0.50_m, 0.0_m, Rotation2d(0_deg) };
            break;
            

            case RevStraight10m:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { -0.35_m, 0.0_m },
                    Translation2d { -0.7_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  -1.0_m,	0.0_m, Rotation2d(0_deg) };
            break;


            case RevStraight15m:
                m_StartPoint = Pose2d {  -0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { -0.5_m, 0.0_m },
                    Translation2d { -1.0_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  -1.50_m,	0.0_m, Rotation2d(0_deg) };
            break;
            
            
            case RevStraight20m:
                m_StartPoint = Pose2d {  -0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { -0.7_m, 0.0_m },
                    Translation2d { -1.4_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  -2.00_m,	0.0_m, Rotation2d(0_deg) };
            break;
            
            
            case RevStraight25m:
                m_StartPoint = Pose2d {  -0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { -0.8_m, 0.0_m },
                    Translation2d { -1.6_m, 0.0_m }
                };

                m_EndPoint = Pose2d {  -2.50_m,	0.0_m, Rotation2d(0_deg) };
            break;









            // ----------------------- COMPLEX PATH TUFF









            case SCurve2:
                m_StartPoint = Pose2d {  0.0_m, 0.0_m, Rotation2d(0_deg) };

                m_Waypoints = 
                {
                    Translation2d { 0.2_m, 0.05_m },
                    Translation2d { 0.235_m, 0.1_m },
                    Translation2d { 0.5_m, 0.18_m },
                    Translation2d { 0.6_m, 0.3_m },
                    Translation2d { 0.72_m, 0.55_m },
                    Translation2d { 0.65_m, 0.8_m },
                    Translation2d { 0.6_m, 0.9_m },
                    Translation2d { 0.55_m, 1.1_m },
                    Translation2d { 0.55_m, 1.3_m },
                    Translation2d { 0.6_m, 1.4_m },
                    Translation2d { 0.68_m, 1.5_m },
                    Translation2d { 0.75_m, 1.55_m },
                    Translation2d { 0.83_m, 1.6_m },
                    Translation2d { 0.95_m, 1.65_m },
                    Translation2d { 1.05_m, 1.68_m },
                    Translation2d { 1.15_m, 1.69_m },
                    Translation2d { 1.20_m, 1.70_m },
                    Translation2d { 1.25_m, 1.70_m }
                };

                m_EndPoint = Pose2d {  1.30_m,	1.7_m, Rotation2d(0_deg) };
            break; 
            
            case SCurve:
                m_StartPoint = Pose2d
                {
                    0.0_m,				// X starting position on field in feet.
                    0.0_m,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };

                m_Waypoints = 
                {
                    Translation2d
                    {
                        0.2_m,				// X of point 1 on field in feet.
                        0.4_m			// Y of point 1 on field in feet.
                    },
                    Translation2d
                    {
                        0.50_m,				// X of point 2 on field in feet.
                        0.9_m			// Y of point 2 on field in feet.
                    }
                };

                m_EndPoint = Pose2d
                {
                    1.10_m,				// X starting position on field in feet.
                    1.38_m,			    // Y starting position on field in feet.
                    Rotation2d(-24_deg)		// Starting rotation on field in degrees.
                };
                break;
        
            
            
            
            
            
            case TrenchtoShoot:
                m_StartPoint = Pose2d
                {
                    18.066_ft,				// X starting position on field in feet.
                    -2.295_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };

                m_Waypoints = 
                {
                    Translation2d
                    {
                        27.402_ft,				// X of point 1 on field in feet.
                        -2.367_ft			// Y of point 1 on field in feet.
                    },
                    Translation2d
                    {
                        32.034_ft,				// X of point 2 on field in feet.
                        -2.547_ft			// Y of point 2 on field in feet.
                    },
                    Translation2d
                    {
                        38.067_ft,				// X of point 2 on field in feet.
                        -4.27_ft			// Y of point 2 on field in feet.
                    }
                };

                m_EndPoint = Pose2d
                {
                    49.664_ft,				// X starting position on field in feet.
                    -8.471_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };
                break;


            case TrenchtoBay:
                m_StartPoint = Pose2d
                {
                    0_ft,				// X starting position on field in feet.
                    0_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };

                m_Waypoints = 
                {
                    Translation2d
                    {
                        2.4_ft,				// X of point 1 on field in feet.
                        -1.6_ft			// Y of point 1 on field in feet.
                    },
                    Translation2d
                    {
                        4.9_ft,				// X of point 2 on field in feet.
                        -2.5_ft			// Y of point 2 on field in feet.
                    },
                    Translation2d
                    {
                        9.5_ft,				// X of point 2 on field in feet.
                        -2.4_ft			// Y of point 2 on field in feet.
                    },
                    Translation2d
                    {
                        11.4_ft,				// X of point 2 on field in feet.
                        -1.0_ft			// Y of point 2 on field in feet.
                    }
                };

                m_EndPoint = Pose2d
                {
                    13.7_ft,				// X starting position on field in feet.
                    -0.8_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };
                break;



            case aTrenchtoShoot:
                m_StartPoint = Pose2d
                {
                    32.098_ft,
                    -2.355_ft,
                    Rotation2d(0_deg)

                };

                m_Waypoints = 
                {
                    Translation2d
                    {
                        37.209_ft,
                        -4.268_ft,
                    },

                    Translation2d
                    {
                        40.783_ft,
                        -9.207_ft
                    },
                
                    Translation2d{
                        40.893_ft,
                        -15.039_ft
                    }

                };

                m_EndPoint = Pose2d
                {
                    43.449_ft,
                    -18.817_ft,
                    Rotation2d(0_deg)

                };
                break;
            
            


            default:
                m_StartPoint = Pose2d
                {
                    0.0_ft,					// X starting position on field in feet.
                    0.0_ft,					// Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };

                m_Waypoints =
                {
                    Translation2d
                    {
                        0.0_ft,				    // X ending position on field in feet.
                        0.0_ft					// Y ending position on field in feet.
                    }
                };
                m_EndPoint = Pose2d
                {
                    0.0_ft,					// X starting position on field in feet.
                    0.0_ft,					// Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                
                };

                break;
        }
    }

    // One-line methods.
    vector<Translation2d> GetSelectedTrajectory() {   return m_Waypoints;     };
    Pose2d GetSelectedTrajectoryStartPoint()      {   return m_StartPoint;    };
    Pose2d GetSelectedTrajectoryEndPoint()        {   return m_EndPoint;      };

private:
    Pose2d m_StartPoint
    {
        0.0_ft,
        0.0_ft,
        Rotation2d(0_deg)
    };

    vector<Translation2d> m_Waypoints
    {
        Translation2d
        {
            0.0_ft,
            0.0_ft
            
        },
        Translation2d
        {
            0.0_ft,
            0.0_ft
            
        }
    };

    Pose2d m_EndPoint
    {
        0.0_ft,
        0.0_ft,
        Rotation2d(0_deg)
    };
};
/////////////////////////////////////////////////////////////////////////////
#endif