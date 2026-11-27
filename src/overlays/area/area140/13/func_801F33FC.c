#include "area140_13.h"

MATCH void func_801F33FC(void) {
    u8 direction;

    direction = SELF(Actor)->direction;
    if (direction != SYS_TestFlag(g_SceneEventFlags, (s32)SELF(Actor)->param.scene_event_flag) && (s8)func_801F3C44(SELF(Actor)->pos.x.fixed | 0x8000, SELF(Actor)->pos.y.fixed | 0x8000) < 0) {
        Area_CellSetPalette((s32)(s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), (s32)(s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1));
        SELF(Actor)->header.step += 1;
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x05));
        }
        func_801F3950(SELF(Actor)->direction, COORD_INT(SELF(Actor)->pos.z));
    }
}
