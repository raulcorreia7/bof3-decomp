#include "area046_13.h"

MATCH s32 func_801F2CE4(s32 entry_x, s32 entry_y) {
    if (entry_y <= 0x218000) {
        if (((u32)((entry_x >> 0x10) - 0xE) < 3U) && (Party_HasVitalItem(4) == 0)) {
            Game_SetScriptActive();
            D_80146865 = 1;
            D_801448EB = 0xB;
            if (g_SceneState.scenario_id < 8) {
                D_801448EC = 0;
                return 1;
            }
            D_801448EC = 0xA;
            return 1;
        }
        return 0;
    }
    return 0;
}
