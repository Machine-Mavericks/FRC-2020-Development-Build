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

enum TrajectoryList {olivia, rTrenchtoShoot, bTrenchtoShoot, rTrenchtoBay, bTrenchtoBay, abTrenchtoShoot, arTrenchtoShoot};//, eFrontShieldGenerator, eSideShieldGenerator, eOpposingTrench, ePowerPort, eTakePowerCells, eDoNothing, eTestPath};

    void SelectTrajectory(TrajectoryList nTrajectory)
    {
        // Retrieve the correct trajectory.
        switch(nTrajectory)
        {
            case rTrenchtoShoot:
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

            case bTrenchtoShoot:
                m_StartPoint = Pose2d
                {
                    34.26_ft,				// X starting position on field in feet.
                    -2.295_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };

                m_Waypoints = 
                {
                    Translation2d
                    {
                        26.648_ft,				// X of point 1 on field in feet.
                        -2.223_ft			// Y of point 1 on field in feet.
                    },
                    Translation2d
                    {
                        16.558_ft,				// X of point 2 on field in feet.
                        -4.162_ft			// Y of point 2 on field in feet.
                    },
                    Translation2d
                    {
                        9.5_ft,				// X of point 2 on field in feet.
                        -2.4_ft			// Y of point 2 on field in feet.
                    }
                };

                m_EndPoint = Pose2d
                {
                    10.203_ft,				// X starting position on field in feet.
                    -7.681_ft,			    // Y starting position on field in feet.
                    Rotation2d(0_deg)		// Starting rotation on field in degrees.
                };
                break;

            case rTrenchtoBay:
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



            case bTrenchtoBay:
                m_StartPoint = Pose2d
                {
                    34.371_ft,
                    -24.587_ft,
                    Rotation2d(0_deg)

                };

                m_Waypoints = 
                {
                    Translation2d
                    {
                        28.79_ft,
                        -24.587_ft,
                    },

                    Translation2d
                    {
                        22.252_ft,
                        -24.556_ft
                    },
                
                    Translation2d{
                        9.348_ft,
                        -20.495_ft
                    }

                };

                m_EndPoint = Pose2d
                {
                    2.56_ft,
                    -18.519_ft,
                    Rotation2d(0_deg)

                };
                break;

            case abTrenchtoShoot:
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
            
            case arTrenchtoShoot:
                            m_StartPoint = Pose2d
                            {
                                21.442_ft,
                                -24.539_ft,
                                Rotation2d(-179.9_deg)

                            };

                            m_Waypoints = 
                            {
                                Translation2d
                                {
                                    17.42_ft,
                                    -21.721_ft,
                                },

                                Translation2d
                                {
                                    15.194_ft,
                                    -16.658_ft
                                },
                            
                            Translation2d
                                {
                                    13.578_ft,
                                    -11.846_ft
                                }
                            };

                            m_EndPoint = Pose2d
                            {
                                10.454_ft,
                                -8.363_ft,
                                Rotation2d(-179.9_deg)

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