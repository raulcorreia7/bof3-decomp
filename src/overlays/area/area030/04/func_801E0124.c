#include "area030_04.h"

/* Resets the AREA030 panel scratch state and queues the cue selected
 * by the current sub-state table entry. */
MATCH void func_801E0124(void) {
    FishingState* record;

    FISHING_STATE->bounce.unk_3C = 0;
    SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 6));

    Area_SceneSelectRecord(*(u16*)(D_801E2ACA + FISHING_STATE->cue_index * 36));

    record        = FISHING_STATE;
    record->flags = (record->flags & ~ACTOR_FLAG_SEMI_TRANSPARENT);

    FISHING_STATE->state_2A = 0;

    FISHING_STATE->counter_48 = 0;
    Script_Select(0);

    record             = FISHING_STATE;
    record->mode_index = (record->mode_index + 1);
}
