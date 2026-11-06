#include "game_00.h"

MATCH void func_801C2538(void) {
    u8  rate;
    u32 step;
    s32 high;
    s32 pos_x;
    s32 pos_y;
    s16 result;

    /* Step size from route kind; rate from the shared selector bundle. */
    rate = g_RouteSpeedScale[g_GameState->counter_11C.u8_value];
    if ((g_Task->direction_08 == 2) || (g_Task->direction_08 == 6)) {
        step           = 0x20;
        g_Task->unk_09 = step;
    } else {
        step           = 0x10;
        g_Task->unk_09 = step;
    }
    g_Task->unk_09 = (g_Task->unk_09 / (rate & BYTE_MASK));
    if ((g_GameFlags & 0x1000) != 0) {
        g_Task->unk_09 *= 2;
    }
    g_Task->vx = g_FacingOffsets[g_Task->direction_08].x * rate;
    high       = g_FacingOffsets[g_Task->direction_08].y * rate;
    g_Task->vy = high;
    pos_x      = g_Task->pos.x.fixed + g_Task->vx * g_Task->unk_09;
    pos_y      = g_Task->pos.y.fixed + high * g_Task->unk_09;
    result     = Area_ReadStepHeight(pos_x, pos_y, g_Task->direction_08);
    if (SP_REF(volatile u8, 0x0u) != 0) {
        result = Area_ReadHeight(pos_x, pos_y);
    }
    g_Task->vz = (result - COORD_INT(g_Task->pos.z)) / g_Task->unk_09;
}
