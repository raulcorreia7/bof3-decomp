#include "area140_13.h"

MATCH void func_801F33FC(void) {
    u8 direction;

    direction = g_SpadWork->direction_08;
    if (direction != SYS_TestFlag(g_SceneEventFlags, (s32)g_SpadWork->unk_0B) &&
        (s8)func_801F3C44(g_SpadWork->x.fixed | 0x8000, g_SpadWork->y.fixed | 0x8000) < 0) {
        Area_SetCellPalette((s32)(s16)((u16)g_SpadWork->x.part.integer + 1),
                            (s32)(s16)((u16)g_SpadWork->y.part.integer + 1));
        g_SpadWork->state_02 += 1;
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x205U);
        }
        func_801F3950(g_SpadWork->direction_08, g_SpadWork->z.part.integer);
    }
}
