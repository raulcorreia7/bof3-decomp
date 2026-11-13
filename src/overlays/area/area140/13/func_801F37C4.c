#include "area140_13.h"

MATCH void func_801F37C4(void) {
    u8 direction;

    direction = g_Task->direction_08;
    if (SYS_TestFlag(g_SceneEventFlags, (s32)g_Task->param.scene_event_flag) == 0) {
        if ((direction ^ 0x1) != 0) {
            goto replay; /* FAKE: both flag branches enter the same block; an if/else duplicate changes the frame */
        }
    } else if (direction != FACING_UP_LEFT) {
    replay:
        Area_SetCellPalette((s32)COORD_INT(g_Task->pos.x), (s32)COORD_INT(g_Task->pos.y));
        Area_SetCellPalette((s32)(s16)((u16)COORD_INT(g_Task->pos.x) + 1), (s32)(s16)((u16)COORD_INT(g_Task->pos.y) + 1));
        g_Task->header.step += 1;
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x05));
        }
        func_801F3950(g_Task->direction_08, COORD_INT(g_Task->pos.z));
    }
}
