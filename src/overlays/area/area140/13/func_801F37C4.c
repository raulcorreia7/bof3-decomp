#include "area140_13.h"

MATCH void func_801F37C4(void) {
    u8 direction;

    direction = g_Task->direction_08;
    if (SYS_TestFlag(g_SceneEventFlags, (s32)g_Task->unk_0B) == 0) {
        if ((direction ^ 1) != 0) {
            goto replay; /* FAKE: both flag branches enter the same block; an if/else duplicate changes the frame */
        }
    } else if (direction != 0) {
    replay:
        Area_SetCellPalette((s32)COORD_INT(g_Task->x), (s32)COORD_INT(g_Task->y));
        Area_SetCellPalette((s32)(s16)((u16)COORD_INT(g_Task->x) + 1), (s32)(s16)((u16)COORD_INT(g_Task->y) + 1));
        g_Task->step += 1;
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(0x205U);
        }
        func_801F3950(g_Task->direction_08, COORD_INT(g_Task->z));
    }
}
