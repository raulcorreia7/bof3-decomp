#include "game_00.h"

MATCH s32 func_801BC4D0(void) {
    u8  saved;
    s32 kind;
    u8  rate;
    s32 result;

    FAKE_STACK_PADS(u8, 0x20); /* FAKE: retail frame reserves 32 unused bytes. */
    saved = g_Task->direction_08;
    kind  = func_801B9598();
    if ((g_Task->direction_08 == FACING_UP_RIGHT) || (g_Task->direction_08 == FACING_DOWN_LEFT)) {
        g_Task->timer = 32;
    } else {
        g_Task->timer = 16;
    }
    rate          = g_RouteSpeedScale[g_Game.current->u.field.counter_11C.u8_value];
    g_Task->timer = (g_Task->timer / (rate & BYTE_MASK));
    if (g_Task->state_70.byte == 0) {
        SP_REF(s32, 0x8) = g_Task->pos.x.fixed + g_FacingOffsets[g_Task->direction_08].x * rate * g_Task->timer;
        SP_REF(s32, 0xC) = g_Task->pos.y.fixed + g_FacingOffsets[g_Task->direction_08].y * rate * g_Task->timer;
    } else {
        SP_REF(s32, 0x8) = g_Task->pos.x.fixed + g_FacingOffsets[g_Task->direction_08].x * rate * g_Task->timer * 2;
        SP_REF(s32, 0xC) = g_Task->pos.y.fixed + g_FacingOffsets[g_Task->direction_08].y * rate * g_Task->timer * 2;
    }
    switch (kind & BYTE_MASK) {
        case 0:
        case 2:
        case 4:
        case 5:
            return 1;
        case 3:
            result = ((s32 (*)(s32, s32, u8))Area_ReadStepHeight)(*(s32*)&D_1F800008, FIELD(s32, (&D_1F800008), 0x4u),
                                                                  g_Task->direction_08);
            if (SP_REF(u8, 0) != 0) {
                if ((s16)result >= 0x41) {
                    g_Task->direction_08 = saved;
                    return 1;
                }
                Area_ReadHeight(*(s32*)&D_1F800008, FIELD(s32, (&D_1F800008), 0x4u));
            }
            return 0;
        case 6:
            return 5;
        case 7:
            return 6;
        default:
            return 0;
    }
}
