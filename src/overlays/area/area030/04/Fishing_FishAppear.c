#include "area030_04.h"

/* Each access reloads the work record and the row, as retail does. */

/* Picks the area's spawn row, randomises the facing and position of
 *           the scratchpad work record from its table byte and the play clock,
 *           then bumps the work step counter. */
/* func_801DE5EC */
#ifdef NON_MATCHING
NON_MATCHING void Fishing_FishAppear(void) {
    s16 limit;
    u8  count;

    Area_SelectSceneRecord(FISHING_ENTRY(FISHING_STATE->cue_index_06)->value_00);
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
    FISHING_STATE->motion_34.unk_34      = TO_COORD(20) - (RANDOM_MASK(0xF) << 0x10);
    FISHING_STATE->y_38.pos_y            = TO_COORD(62) - (FISHING_ROW->facing_92 * TO_COORD(12)) - (RANDOM_MASK(0xF) << 0x10);
    FISHING_STATE->bounce_3C.half.key_3E = (s16)((-(FISHING_ENTRY(FISHING_STATE->cue_index_06)->count_0A << 0x18) >> 0x10) - (RANDOM_MASK(7) << 5));
    limit                                = Area_SampleHeight(FISHING_STATE->motion_34.unk_34, FISHING_STATE->y_38.pos_y);
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
INCLUDE_ASM(Fishing_FishAppear);
#endif
