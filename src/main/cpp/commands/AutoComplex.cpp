/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoComplex.h"
#include "commands/drive/StraightDistance.h"
#include "commands/drive/TurnLeftToHex.h"
#include "commands/drive/TurnRightToHex.h"
#include "commands/drive/FollowPath.h"


AutoComplex::AutoComplex() {
    AddCommands(
        StraightDistance(-7.0, 0.5, 0.5),
       // FollowPath(CTrajectoryConstants::arTrenchtoShoot, false),
        TurnRightToHex());


}


