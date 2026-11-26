#include "area030_04.h"

/* Picks the spawn row, randomises the work record's facing and position from its cue row and the
 * play clock, then bumps the step counter. */
MATCH void Fishing_FishAppear(void) {
    s16 limit;
    s32 coord;

    Area_SceneSelectRecord(FISHING_ENTRY(TASK(FishingState)->cue_index)->scene_id);
    TASK(FishingState)->active_flags = 0;
    TASK(FishingState)->counter_48   = 2;
    TASK(FishingState)->state_29     = 5;
    TASK(FishingState)->timer        = 0;
    TASK(FishingState)->saved_index  = 0;
    FISHING_ROW->fish_row            = (u8)RANDOM_MASK(3);
    if ((u32)FISHING_ROW->fish_row < (u32)D_801E2AD2[TASK(FishingState)->cue_index * sizeof(FishingSceneCue)]) {
        FISHING_ROW->fish_row = D_801E2AD2[TASK(FishingState)->cue_index * sizeof(FishingSceneCue)];
    }
    FISHING_ROW->fish_row &= 3;
    coord                             = TO_COORD(20);
    TASK(FishingState)->motion.unk_34 = coord - (RANDOM_MASK(0xF) << 0x10);
    coord                             = TO_COORD(62);
    coord -= FISHING_ROW->fish_row * TO_COORD(12);
    coord -= RANDOM_MASK(0xF) << 0x10;
    TASK(FishingState)->y_38.pos_y      = coord;
    coord                               = -(D_801E2AD2[(s16)(TASK(FishingState)->cue_index * sizeof(FishingSceneCue))] << 0x18);
    TASK(FishingState)->bounce.half.key = (s16)((coord >> 0x10) - (RANDOM_MASK(7) << 5));
    limit                               = Area_HeightSample(TASK(FishingState)->motion.unk_34, TASK(FishingState)->y_38.pos_y);
    if (TASK(FishingState)->bounce.half.key == 0) {
        TASK(FishingState)->bounce.half.key = -0x20;
    } else if (TASK(FishingState)->bounce.half.key < limit) {
        TASK(FishingState)->bounce.half.key = limit;
    }
    TASK(FishingState)->counter_08   = 4;
    TASK(FishingState)->bounce_speed = 0;
    Script_Select(0);
    TASK(FishingState)->handler_index += 1;
}
