#include "area140_13.h"

MATCH void func_801F37C4(void) {
    u8 direction;

    direction = g_SpadWork->direction_08;
    if (SYS_TestFlag(g_SceneEventFlags, (s32)g_SpadWork->unk_0B) == 0) {
        if ((direction ^ 1) != 0) {
            goto replay; /* FAKE: both flag branches enter the same block; an if/else duplicate changes the frame */
        }
    } else if (direction != 0) {
    replay:
        Area_SetCellPalette((s32)g_SpadWork->x.part.integer, (s32)g_SpadWork->y.part.integer);
        Area_SetCellPalette((s32)(s16)((u16)g_SpadWork->x.part.integer + 1),
                            (s32)(s16)((u16)g_SpadWork->y.part.integer + 1));
        g_SpadWork->state_02 += 1;
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x205U);
        }
        func_801F3950(g_SpadWork->direction_08, g_SpadWork->z.part.integer);
    }
}
