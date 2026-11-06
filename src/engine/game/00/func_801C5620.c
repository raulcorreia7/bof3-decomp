#include "game_00.h"

MATCH void func_801C5620(void) {
    u16 count;
    s32 x;
    s32 y;
    s16 result;

    x                    = g_Task->x.fixed;
    count                = COORD_INT(g_Task->z);
    y                    = g_Task->y.fixed;
    COORD_INT(g_Task->z) = count - 16;
    result               = Area_ReadHeight(x, y);

    if ((s16)COORD_INT(g_Task->z) < result) {
        COORD_INT(g_Task->z) = (u16)result;
        Actor_SelectScript(g_Task->direction_08);
        GFX_StagePalette(0x80035600u + g_Task->unk_05 * 0x40u, 0);
        g_GameState->mode_12B.u8_value = 0;
        g_Task->mode                   = 1;
        ACTOR_CLEAR_STEP();
    }

    func_8014D978();
}
