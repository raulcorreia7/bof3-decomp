#include "area167_13.h"

MATCH void func_801F37A8(void) {
    if (g_AreaSceneMode == 0x20) {
        if (g_GameStateIndex == 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
        }
        g_Task->header.step += 1;
    }

    if (SYS_TestFlag(g_SceneEventFlags, 143)) {
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(g_Task->pos.x) + 1) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(g_Task->pos.y) << 16)) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(g_Task->pos.y) + 1) << 16)) <= TO_COORD(1)) {
                if (g_GameStateIndex == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
                }
                g_Task->header.step += 1;
            }
        }
    }

    Area_Update();
}
