/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoSimple.h"
#include "commands/drive/StraightDistance.h"
#include "commands/drive/TurnLeftToHex.h"
#include "commands/drive/TurnRightToHex.h"
#include "commands/drive/FollowPath.h"
#include "commands/ShootBalls.h"
#include "commands/TiltDownUp.h"
#include "commands/IntakeOnOff.h"

AutoSimple::AutoSimple() {
    AddCommands(
        TiltDownUp(TiltDownUp::TiltDown),
        FollowPath(CTrajectoryConstants::Straight1m, false),
        TurnRightToHex(),
        ShootBalls(),
        IntakeOnOff(true),
        FollowPath(CTrajectoryConstants::SCurve, false),
        FollowPath(CTrajectoryConstants::Straight1m, false),
        FollowPath(CTrajectoryConstants::Straight1m, false)
        );
}


