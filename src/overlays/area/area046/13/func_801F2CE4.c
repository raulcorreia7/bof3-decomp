#include "area046_13.h"

MATCH s32 func_801F2CE4(s32 entry_x, s32 entry_y) {
    if (entry_y <= TO_COORD(33) + COORD_HALF) {
        if ((((entry_x >> 0x10) - 14) < 3U) && (Item_VitalHas(VITAL_ITEM_PASSPORT) == 0)) {
            Game_SetScriptActive();
            g_ScriptVars[1]        = 1;
            g_SceneEventState.mode = 0xB;
            if (g_ScenarioState.scenario_id < 8) {
                g_SceneEventState.step = 0;
                return 1;
            }
            g_SceneEventState.step = 0xA;
            return 1;
        }
        return 0;
    }
    return 0;
}
