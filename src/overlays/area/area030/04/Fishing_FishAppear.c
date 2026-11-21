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
    s32 coord;

    Area_SelectSceneRecord(FISHING_ENTRY(FISHING_STATE->cue_index)->scene_id);
    FISHING_STATE->active_flags = 0;
    FISHING_STATE->counter_48   = 2;
    FISHING_STATE->state_29     = 5;
    FISHING_STATE->step_timer   = 0;
    FISHING_STATE->saved_index  = 0;
    FISHING_ROW->fish_row       = (u8)RANDOM_MASK(3);
    count                       = FISHING_ENTRY(FISHING_STATE->cue_index)->count;
    if ((u32)FISHING_ROW->fish_row < (u32)count) {
        FISHING_ROW->fish_row = count;
    }
    FISHING_ROW->fish_row &= 3;
    coord                        = TO_COORD(20);
    FISHING_STATE->motion.unk_34 = coord - (RANDOM_MASK(0xF) << 0x10);
    coord                        = TO_COORD(62);
    coord -= FISHING_ROW->fish_row * TO_COORD(12);
    coord -= RANDOM_MASK(0xF) << 0x10;
    FISHING_STATE->y_38.pos_y      = coord;
    coord                          = -(D_801E2AD2[FISHING_STATE->cue_index * sizeof(FishingSceneCue)] << 0x18);
    FISHING_STATE->bounce.half.key = (s16)((coord >> 0x10) - (RANDOM_MASK(7) << 5));
    limit                          = Area_SampleHeight(FISHING_STATE->motion.unk_34, FISHING_STATE->y_38.pos_y);
    if (FISHING_STATE->bounce.half.key == 0) {
        FISHING_STATE->bounce.half.key = -0x20;
    } else if (FISHING_STATE->bounce.half.key < limit) {
        FISHING_STATE->bounce.half.key = limit;
    }
    FISHING_STATE->counter_08 = 4;
    FISHING_STATE->step_14    = 0;
    Script_Select(0);
    FISHING_STATE->handler_index += 1;
}
#else
INCLUDE_ASM(Fishing_FishAppear);
#endif
