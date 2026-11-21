#include "area018_13.h"

MATCH s32 func_801F2C04(void) {
    if (g_ScenarioState.scenario_id == 8) {
        g_EncounterZones[g_GameAreaId][0].rate = 0;
    } else {
        g_EncounterZones[g_GameAreaId][0].rate = 2;
    }
}
