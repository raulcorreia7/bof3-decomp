#include "area140_13.h"

MATCH void func_801F33FC(void) {
    u8 direction;

    direction = TASK(Actor)->direction;
    if (direction != SYS_TestFlag(g_SceneEventFlags, (s32)TASK(Actor)->param.scene_event_flag) && (s8)func_801F3C44(TASK(Actor)->pos.x.fixed | 0x8000, TASK(Actor)->pos.y.fixed | 0x8000) < 0) {
        Area_CellSetPalette((s32)(s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), (s32)(s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1));
        TASK(Actor)->header.step += 1;
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x05));
        }
        func_801F3950(TASK(Actor)->direction, COORD_INT(TASK(Actor)->pos.z));
    }
}
