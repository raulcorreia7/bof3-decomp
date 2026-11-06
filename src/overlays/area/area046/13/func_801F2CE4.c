#include "area046_13.h"

MATCH s32 func_801F2CE4(s32 entry_x, s32 entry_y) {
    if (entry_y <= 0x218000) {
        if ((((entry_x >> 0x10) - 0xE) < 3U) && (Item_VitalHas(4) == 0)) {
            Game_SetScriptActive();
            D_80146865                  = 1;
            g_SaveData.scene_event.mode = 0xB;
            if (g_SceneState.scenario_id < 8) {
                g_SaveData.scene_event.step = 0;
                return 1;
            }
            g_SaveData.scene_event.step = 0xA;
            return 1;
        }
        return 0;
    }
    return 0;
}
