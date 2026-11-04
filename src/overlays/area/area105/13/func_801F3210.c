#include "area105_13.h"

MATCH s32 func_801F3210(s32 x, s32 y) {
    u32 facing;

    if (g_SceneState.scenario_id < 0xA) {
        if (D_80143F03 == 0) {
            facing        = D_80145E98;
            SP_REF(u8, 0) = D_80145E98;
            if (facing >= 2U) {
                if (facing != 2) {
                    if ((y >> 16) >= 0x1E) {
                        Game_SetScriptActive();
                        D_801448EB = 0x3D;
                        D_801448EC = 0;
                        return 1;
                    }
                    return 0;
                }
                return 0;
            }
        }
        return 0;
    }
    return 0;
}
