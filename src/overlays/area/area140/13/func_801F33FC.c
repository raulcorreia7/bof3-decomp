#include "area140_13.h"

MATCH void func_801F33FC(void) {
    u8 direction;

    direction = g_Task->direction_08;
    if (direction != SYS_TestFlag(g_SceneEventFlags, g_Task->unk_0B) &&
        (s8)func_801F3C44(g_Task->x.fixed | 0x8000, g_Task->y.fixed | 0x8000) < 0) {
        Area_SetCellPalette((s16)(g_Task->x.part.integer + 1), (s16)(g_Task->y.part.integer + 1));
        g_Task->step += 1;
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(0x205U);
        }
        func_801F3950(g_Task->direction_08, g_Task->z.part.integer);
    }
}
