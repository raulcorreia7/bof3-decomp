#include "game_00.h"

MATCH void func_801C5620(void) {
    u16 count;
    s32 x;
    s32 y;
    s16 result;

    x                        = g_Task->pos.x.fixed;
    count                    = COORD_INT(g_Task->pos.z);
    y                        = g_Task->pos.y.fixed;
    COORD_INT(g_Task->pos.z) = count - 16;
    result                   = Area_ReadHeight(x, y);

    if ((s16)COORD_INT(g_Task->pos.z) < result) {
        COORD_INT(g_Task->pos.z) = (u16)result;
        Actor_SelectScript(g_Task->direction_08);
        GFX_LoadPalette(GAME_PALETTE_STAGE + g_Task->unk_05 * 0x40u, 0);
        g_Game.current->u.field.mode_12B.u8_value = 0;
        g_Task->header.mode                       = 1;
        ACTOR_CLEAR_STEP();
    }

    Actor_StepAnimLoop();
}
