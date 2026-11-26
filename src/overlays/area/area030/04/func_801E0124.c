#include "area030_04.h"

/* Resets the AREA030 panel scratch state and queues the cue selected
 * by the current sub-state table entry. */
MATCH void func_801E0124(void) {
    FishingState* record;

    SELF(FishingState)->bounce.unk_3C = 0;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));

    Area_SceneSelectRecord(*(u16*)(D_801E2ACA + SELF(FishingState)->cue_index * 36));

    record        = SELF(FishingState);
    record->flags = (record->flags & ~ACTOR_FLAG_SEMI_TRANSPARENT);

    SELF(FishingState)->state_2A = 0;

    SELF(FishingState)->counter_48 = 0;
    Script_Select(0);

    record             = SELF(FishingState);
    record->mode_index = (record->mode_index + 1);
}
