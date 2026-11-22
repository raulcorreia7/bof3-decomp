#include "area140_13.h"

MATCH void func_801F37C4(void) {
    u8 direction;

    direction = TASK(Actor)->direction;
    if (SYS_TestFlag(g_SceneEventFlags, (s32)TASK(Actor)->param.scene_event_flag) == 0) {
        if ((direction ^ 0x1) != 0) {
            goto replay; /* FAKE: both flag branches enter the same block; an if/else duplicate changes the frame */
        }
    } else if (direction != FACING_UP_LEFT) {
    replay:
        Area_CellSetPalette((s32)COORD_INT(TASK(Actor)->pos.x), (s32)COORD_INT(TASK(Actor)->pos.y));
        Area_CellSetPalette((s32)(s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), (s32)(s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1));
        TASK(Actor)->header.step += 1;
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x05));
        }
        func_801F3950(TASK(Actor)->direction, COORD_INT(TASK(Actor)->pos.z));
    }
}
