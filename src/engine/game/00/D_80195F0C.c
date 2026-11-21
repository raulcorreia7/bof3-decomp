#include "game_00.h"

char D_80195F0C[4] = "%d";

AreaActionAltSteps g_AreaActionAltSteps = {
    AreaAction_RollAltStep,
    AreaAction_FindSmall,
    AreaAction_FindLarge,
    AreaAction_End,
    AreaAction_WaitMessage,
};
