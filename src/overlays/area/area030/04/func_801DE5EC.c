#include "area030_04.h"

/* Each access reloads the work record and the row, as retail does. */

/* Picks the area's spawn row, randomises the facing and position of
 *           the scratchpad work record from its table byte and the play clock,
 *           then bumps the work step counter. */
/* nonmatching unmeasured: tried the bounce count in a local (68.75); the negated scale in a local (66.21); the unsigned
 * facing comparison with a count local (74.31); the area-table entry taken as a pointer instead of a 0x24-byte rvalue
 * (74.31, byte-identical, so the rvalue was never the frame's cause). The candidate's frame is 0x28 where the retail's
 * is 0x18, and it keeps the table base in s0 where the retail rematerialises it per access (lhu %lo(D_801E2AC8)($at)
 * and lbu %lo(D_801E2AD2)($at) at 0x801DE61C and 0x801DE6B4). resume: a source shape that keeps the table base out of a
 * callee-saved register and drops the frame to the retail's 0x18. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DE5EC(void) {
    s16 limit;
    u8  count;

    Area_FindSceneRecord(FISHING_ENTRY(FISHING_STATE->cue_index_06)->value_00);
    FISHING_STATE->active_flags   = 0;
    FISHING_STATE->counter_48     = 2;
    FISHING_STATE->state_29       = 5;
    FISHING_STATE->step_timer_09  = 0;
    FISHING_STATE->saved_index_0B = 0;
    FISHING_ROW->facing_92        = (u8)RANDOM_MASK(3);
    count                         = FISHING_ENTRY(FISHING_STATE->cue_index_06)->count_0A;
    if ((u32)FISHING_ROW->facing_92 < (u32)count) {
        FISHING_ROW->facing_92 = count;
    }
    FISHING_ROW->facing_92 &= 3;
    FISHING_STATE->motion_34.pos.pos.x.raw = TO_COORD(20) - (RANDOM_MASK(0xF) << 0x10);
    FISHING_STATE->y_38.pos_y              = TO_COORD(62) - (FISHING_ROW->facing_92 * TO_COORD(12)) - (RANDOM_MASK(0xF) << 0x10);
    FISHING_STATE->bounce_3C.half.key_3E =
        (s16)((-(FISHING_ENTRY(FISHING_STATE->cue_index_06)->count_0A << 0x18) >> 0x10) - (RANDOM_MASK(7) << 5));
    limit = Area_SampleHeight(FISHING_STATE->motion_34.pos.pos.x.raw, FISHING_STATE->y_38.pos_y);
    if (FISHING_STATE->bounce_3C.half.key_3E == 0) {
        FISHING_STATE->bounce_3C.half.key_3E = -0x20;
    } else if (FISHING_STATE->bounce_3C.half.key_3E < limit) {
        FISHING_STATE->bounce_3C.half.key_3E = limit;
    }
    FISHING_STATE->counter_08 = 4;
    FISHING_STATE->step_14    = 0;
    Actor_SelectScript(0);
    FISHING_STATE->handler_index_01 += 1;
}
#else
INCLUDE_ASM(func_801DE5EC);
#endif
