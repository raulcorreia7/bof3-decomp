#include "game_00.h"

MATCH s32 func_801BC4D0(void) {
    u8  saved;
    s32 kind;
    u8  rate;
    s32 result;

    STACK_PADS(u8, 0x20); /* FAKE: retail frame reserves 32 unused bytes. */
    saved = g_SpadWork->direction_08;
    kind  = func_801B9598();
    if ((g_SpadWork->direction_08 == 2) || (g_SpadWork->direction_08 == 6)) {
        g_SpadWork->unk_09 = 0x20;
    } else {
        g_SpadWork->unk_09 = 0x10;
    }
    rate               = g_RouteSpeedScale[g_GameState->counter_11C.u8_value];
    g_SpadWork->unk_09 = (u8)(g_SpadWork->unk_09 / (u32)(rate & BYTE_MASK));
    if (g_SpadWork->state_70.byte == 0) {
        SP_REF(s32, 0x8) =
            g_SpadWork->x.fixed + g_FacingOffsets[g_SpadWork->direction_08].x * rate * g_SpadWork->unk_09;
        SP_REF(s32, 0xC) =
            g_SpadWork->y.fixed + g_FacingOffsets[g_SpadWork->direction_08].y * rate * g_SpadWork->unk_09;
    } else {
        SP_REF(s32, 0x8) =
            g_SpadWork->x.fixed + g_FacingOffsets[g_SpadWork->direction_08].x * rate * g_SpadWork->unk_09 * 2;
        SP_REF(s32, 0xC) =
            g_SpadWork->y.fixed + g_FacingOffsets[g_SpadWork->direction_08].y * rate * g_SpadWork->unk_09 * 2;
    }
    switch (kind & BYTE_MASK) {
        case 0:
        case 2:
        case 4:
        case 5:
            return 1;
        case 3:
            result = ((s32 (*)(s32, s32, u8))Area_ReadStepHeight)(*(s32*)&D_1F800008, FIELD(s32, (&D_1F800008), 0x4u),
                                                                  g_SpadWork->direction_08);
            if (SP_REF(u8, 0) != 0) {
                if ((s16)result >= 0x41) {
                    g_SpadWork->direction_08 = saved;
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
