#include "game_00.h"

MATCH void func_801C5620(void) {
    u16 count;
    s32 x;
    s32 y;
    s16 result;

    x                      = g_Task->x.fixed;
    count                  = g_Task->z.part.integer;
    y                      = g_Task->y.fixed;
    g_Task->z.part.integer = count - 16;
    result                 = Area_ReadHeight(x, y);

    if ((s16)g_Task->z.part.integer < result) {
        g_Task->z.part.integer = (u16)result;
        Actor_SelectScript(g_Task->direction_08);
        GFX_StagePalette(0x80035600u + g_Task->unk_05 * 0x40u, 0);
        g_GameState->mode_12B.u8_value = 0;
        g_Task->mode                   = 1;
        ACTOR_CLEAR_STATE();
    }

    func_8014D978();
}
