/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/* DashboardOI Class is the interface to the FRC robot dashboard - used to display current robot data*/

#pragma once

//using namespace frc;

class DashboardOI {
    public:
    
    // class constructor - executed upon creation of DashboardOI object
    DashboardOI();

    // Update dashboard
    void UpdateDashBoard(void);
};