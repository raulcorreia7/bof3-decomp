#include "game_00.h"

MATCH s32 func_801BC4D0(void) {
    u8  saved;
    s32 type;
    u8  rate;
    s32 result;

    FAKE_STACK_PADS(u8, 0x20); /* FAKE: retail frame reserves 32 unused bytes. */
    saved = SELF(Actor)->direction;
    type  = func_801B9598();
    if ((SELF(Actor)->direction == FACING_UP_RIGHT) || (SELF(Actor)->direction == FACING_DOWN_LEFT)) {
        SELF(Actor)->timer = 32;
    } else {
        SELF(Actor)->timer = 16;
    }
    rate               = g_RouteSpeedScale[g_Game.current->u.field.counter.unsigned_value];
    SELF(Actor)->timer = (SELF(Actor)->timer / (rate & BYTE_MASK));
    if (SELF(Actor)->voice_flags.scene_flag == 0) {
        SP_REF(s32, 0x8) = SELF(Actor)->pos.x.fixed + g_FacingOffsets[SELF(Actor)->direction].x * rate * SELF(Actor)->timer;
        SP_REF(s32, 0xC) = SELF(Actor)->pos.y.fixed + g_FacingOffsets[SELF(Actor)->direction].y * rate * SELF(Actor)->timer;
    } else {
        SP_REF(s32, 0x8) = SELF(Actor)->pos.x.fixed + g_FacingOffsets[SELF(Actor)->direction].x * rate * SELF(Actor)->timer * 2;
        SP_REF(s32, 0xC) = SELF(Actor)->pos.y.fixed + g_FacingOffsets[SELF(Actor)->direction].y * rate * SELF(Actor)->timer * 2;
    }
    switch (type & BYTE_MASK) {
        case 0:
        case 2:
        case 4:
        case 5:
            return 1;
        case 3:
            result = ((s32 (*)(s32, s32, u8))Area_HeightReadStep)(*(s32*)&g_ScratchPad.cells.halves[4], FIELD(s32, (&g_ScratchPad.cells.halves[4]), 0x4u), SELF(Actor)->direction);
            if (SP_REF(u8, 0) != 0) {
                if ((s16)result >= 0x41) {
                    SELF(Actor)->direction = saved;
                    return 1;
                }
                Area_HeightRead(*(s32*)&g_ScratchPad.cells.halves[4], FIELD(s32, (&g_ScratchPad.cells.halves[4]), 0x4u));
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
