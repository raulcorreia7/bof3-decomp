#include "area018_13.h"

MATCH s32 func_801F2C04(void) {
    if (g_SceneState.scenario_id == 8) {
        g_EncounterZoneLists[g_GameAreaId][4] = 0;
    } else {
        g_EncounterZoneLists[g_GameAreaId][4] = 2;
    }
}
