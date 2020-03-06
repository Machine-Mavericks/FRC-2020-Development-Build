/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/* DashboardOI Class is the interface to the FRC robot dashboard - used to display current robot data*/

#include <frc/Shuffleboard/Shuffleboard.h>
#include <frc2/Timer.h>

#pragma once

using namespace frc;

class DashboardOI {
    public:
    
    // class constructor - executed upon creation of DashboardOI object
    DashboardOI();

    //create timer
    frc2::Timer *m_Timer;

    // Update dashboard
    void UpdateDashBoard(void);

    // initialize dashboard
    void InitializeDashBoard(void);

    // returns state of command switches
    bool GetAutoCommandState1(void);
    bool GetAutoCommandState2(void);
    bool GetAutoCommandState3(void);

    private:

    void InitializeCommandsPage(void);

    nt::NetworkTableEntry AutoCommand1;
    nt::NetworkTableEntry AutoCommand2;
    nt::NetworkTableEntry AutoCommand3;
    nt::NetworkTableEntry TimeLeft;
};