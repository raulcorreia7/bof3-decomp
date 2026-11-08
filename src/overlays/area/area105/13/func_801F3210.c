#include "area105_13.h"

MATCH s32 func_801F3210(s32 x, s32 y) {
    u32 facing;

    if (g_SceneState.scenario_id < 0xA) {
        if (D_80143F03 == 0) {
            facing        = g_Game.members[0].facing;
            SP_REF(u8, 0) = g_Game.members[0].facing;
            if (facing >= 2U) {
                if (facing != FACING_UP_RIGHT) {
                    if ((y >> 16) >= 30) {
                        Scene_StartEvent(0x3D, 0);
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
