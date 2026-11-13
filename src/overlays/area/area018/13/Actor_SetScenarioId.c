#include "area018_13.h"

/* func_801F2C04 */
MATCH s32 Actor_SetScenarioId(void) {
    if (g_SceneState.scenario_id == 8) {
        g_EncounterZones[g_GameAreaId][4] = 0;
    } else {
        g_EncounterZones[g_GameAreaId][4] = 2;
    }
}
