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

enum TrajectoryList {Straight1m, SCurve, olivia, ShootBay, BayShoot};
    void SelectTrajectory(TrajectoryList nTrajectory)
    {
        // Retrieve the correct trajectory.
        switch(nTrajectory)
        {
            case Straight1m:
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
                        0.5_m,				// X of point 1 on field in feet.
                        0.0_m			// Y of point 1 on field in feet.
                    },
                    Translation2d
                    {
                        1.0_m,				// X of point 2 on field in feet.
                        0.0_m			// Y of point 2 on field in feet.
                    }
                };

                m_EndPoint = Pose2d
                {
                    1.50_m,				// X starting position on field in feet.
                    0.0_m,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };
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
                    Rotation2d(-23_deg)		// Starting rotation on field in degrees.
                };
                break;
        
            
            
            
            
            
            case BayShoot:
                m_StartPoint = Pose2d
                {
                    0.0_ft,				// X starting position on field in feet.
                    0.0_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };

                m_Waypoints = 
                {
                    Translation2d
                    {
                        -2.499_ft,				// X of point 1 on field in feet.
                        -15.041_ft			// Y of point 1 on field in feet.
                    },
                    Translation2d
                    {
                        -5.495_ft,				// X of point 2 on field in feet.
                        -14.991_ft			// Y of point 2 on field in feet.
                    },
                    Translation2d
                    {
                        -7.947_ft,				// X of point 2 on field in feet.
                        -13.823_ft			// Y of point 2 on field in feet.
                    }
                };

                m_EndPoint = Pose2d
                {
                     -9.843_ft,				// X starting position on field in feet.
                    -13.183_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };
                break;

            case ShootBay:
                m_StartPoint = Pose2d
                {
                    0.647_ft,				// X starting position on field in feet.
                    -5.646_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };

                m_Waypoints = 
                {
                    Translation2d
                    {
                        3.248_ft,				// X of point 1 on field in feet.
                        -6.792_ft			// Y of point 1 on field in feet.
                    },
                    Translation2d
                    {
                        5.834_ft,				// X of point 2 on field in feet.
                        -7.445_ft			// Y of point 2 on field in feet.
                    },
                    Translation2d
                    {
                        8.684_ft,				// X of point 2 on field in feet.
                        -7.533_ft			// Y of point 2 on field in feet.
                    }
                };

                m_EndPoint = Pose2d
                {
                    10.328_ft,				// X starting position on field in feet.
                    -7.533_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };
                break;

            
//trajectory = TrajectoryGenerator::GenerateTrajectory(
//        frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
//        {frc::Translation2d(2.5_m, -1.3_m),
 //       frc::Translation2d(4.75_m, -2.4_m),
//        frc::Translation2d(7.06_m, -2.58_m),
//        frc::Translation2d(9.02_m, -2.2_m),
//        frc::Translation2d(11.22_m, -1.24_m)},
//        frc::Pose2d(13.7_m, -0.8_m, frc::Rotation2d(0_deg)),
//        pathconfig);

            case olivia:
                            m_StartPoint = Pose2d
                            {
                                0_m, 0_m, frc::Rotation2d(0_deg)

                            };

                            m_Waypoints = 
                            {
                                Translation2d
                                {
                                    2.5_m, -1.3_m
                                },

                                Translation2d
                                {
                                    4.75_m, -2.4_m
                                },
                            
                            Translation2d
                                {
                                   7.06_m, -2.58_m
                                },
                            
                            Translation2d
                                {
                                   9.02_m, -2.2_m
                                },
                            Translation2d
                                {
                                   11.22_m, -1.24_m
                                }
                            };

                            m_EndPoint = Pose2d
                            {
                                13.7_m, -0.8_m, frc::Rotation2d(0_deg)

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