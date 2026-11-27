#include "area167_13.h"

MATCH void func_801F37A8(void) {
    if (g_AreaSceneMode == 0x20) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
        }
        SELF(Actor)->header.step += 1;
    }

    if (SYS_TestFlag(g_SceneEventFlags, 143)) {
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(SELF(Actor)->pos.x) + 1) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(SELF(Actor)->pos.y) << 16)) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(SELF(Actor)->pos.y) + 1) << 16)) <= TO_COORD(1)) {
                if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
                }
                SELF(Actor)->header.step += 1;
            }
        }
    }

    Area_Update();
}
