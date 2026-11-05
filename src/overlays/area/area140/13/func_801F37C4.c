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
        Area_SetCellPalette((s32)g_Task->x.part.integer, (s32)g_Task->y.part.integer);
        Area_SetCellPalette((s32)(s16)((u16)g_Task->x.part.integer + 1), (s32)(s16)((u16)g_Task->y.part.integer + 1));
        g_Task->step += 1;
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(0x205U);
        }
        func_801F3950(g_Task->direction_08, g_Task->z.part.integer);
    }
}
