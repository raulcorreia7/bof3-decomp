#include "area030_04.h"

/* Picks the spawn row, randomises the work record's facing and position from its cue row and the
 * play clock, then bumps the step counter. */
MATCH void Fishing_FishAppear(void) {
    s16 limit;
    s32 coord;

    Area_SceneSelectRecord(FISHING_ENTRY(SELF(FishingState)->cue_index)->scene_id);
    SELF(FishingState)->active_flags = 0;
    SELF(FishingState)->counter_48   = 2;
    SELF(FishingState)->state_29     = 5;
    SELF(FishingState)->timer        = 0;
    SELF(FishingState)->saved_index  = 0;
    FISHING_ROW->fish_row            = (u8)RANDOM_MASK(3);
    if ((u32)FISHING_ROW->fish_row < (u32)D_801E2AD2[SELF(FishingState)->cue_index * sizeof(FishingSceneCue)]) {
        FISHING_ROW->fish_row = D_801E2AD2[SELF(FishingState)->cue_index * sizeof(FishingSceneCue)];
    }
    FISHING_ROW->fish_row &= 3;
    coord                             = TO_COORD(20);
    SELF(FishingState)->motion.unk_34 = coord - (RANDOM_MASK(0xF) << 0x10);
    coord                             = TO_COORD(62);
    coord -= FISHING_ROW->fish_row * TO_COORD(12);
    coord -= RANDOM_MASK(0xF) << 0x10;
    SELF(FishingState)->y_38.pos_y      = coord;
    coord                               = -(D_801E2AD2[(s16)(SELF(FishingState)->cue_index * sizeof(FishingSceneCue))] << 0x18);
    SELF(FishingState)->bounce.half.key = (s16)((coord >> 0x10) - (RANDOM_MASK(7) << 5));
    limit                               = Area_HeightSample(SELF(FishingState)->motion.unk_34, SELF(FishingState)->y_38.pos_y);
    if (SELF(FishingState)->bounce.half.key == 0) {
        SELF(FishingState)->bounce.half.key = -0x20;
    } else if (SELF(FishingState)->bounce.half.key < limit) {
        SELF(FishingState)->bounce.half.key = limit;
    }
    SELF(FishingState)->counter_08   = 4;
    SELF(FishingState)->bounce_speed = 0;
    Script_Select(0);
    SELF(FishingState)->handler_index += 1;
}
