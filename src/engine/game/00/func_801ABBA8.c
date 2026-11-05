#include "game_00.h"

MATCH void func_801ABBA8(void* sub, s32 route) {
    u8  rate;
    u8  masked;
    u8  slot;
    s32 high;
    s32 pos_x;
    s32 pos_y;
    s16 result;

    masked = route & BYTE_MASK;
    slot   = route & BYTE_MASK;
    rate   = g_RouteSpeedScale[((u8*)sub)[4]];
    if ((masked == 2) || (masked == 6)) {
        g_SpadWork->unk_09 = 0x20;
    } else {
        g_SpadWork->unk_09 = 0x10;
    }
    g_SpadWork->unk_09 = (u8)(g_SpadWork->unk_09 / (u32)(rate & BYTE_MASK));
    g_SpadWork->vx     = g_FacingOffsets[slot].x * rate;
    high               = g_FacingOffsets[slot].y * rate;
    g_SpadWork->vy     = high;
    pos_x              = g_SpadWork->x.fixed + g_SpadWork->vx * g_SpadWork->unk_09;
    pos_y              = g_SpadWork->y.fixed + high * g_SpadWork->unk_09;
    if ((((u8*)sub)[0] & 0x80) == 0) {
        result = func_80154ABC(pos_x, pos_y, slot, sub);
        if (SP_REF(volatile u8, 0x0u) != 0) {
            result = Area_SampleHeight(pos_x, pos_y);
        }
        g_SpadWork->vz = (result - g_SpadWork->z.part.integer) / g_SpadWork->unk_09;
    }
    g_SpadWork->flags_00 |= ACTOR_FLAG_STEP_MOVE;
}
