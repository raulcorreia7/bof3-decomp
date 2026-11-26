#include "area112_13.h"

/* Runs the answer cell the party stands on: the first cell whose leader is not
 * facing right sets its scene flag and the direction flags its mask names. */
MATCH u8 func_801F3A14(u8 x, u8 y) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        if (x == D_801F4908[i].x && y == D_801F4908[i].y && g_Game.members[0].facing != FACING_RIGHT) {
            break;
        }
    }
    if (i == 4) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, D_801F4908[i].flag_id) != 0) {
        return 0;
    }
    if ((func_801F3CF0() & BYTE_MASK) != 0) {
        Scene_StartEvent(SCENE_EVENT_INN, 10);
        g_SceneEventState.selection = 0x15;
        return 0;
    }
    for (j = 0; j < 8; j++) {
        if ((D_801F4908[i].flag_mask >> j) & 1) {
            if (j < 4) {
                SYS_ClearFlag(g_SceneEventFlags, D_801F4928[j & 0x3]);
            } else {
                SYS_SetFlag(g_SceneEventFlags, D_801F4928[j & 0x3]);
            }
        }
    }
    SYS_SetFlag(g_SceneEventFlags, D_801F4908[i].flag_id);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
    Scene_StartToggleLock(0xF);
    return 1;
}
