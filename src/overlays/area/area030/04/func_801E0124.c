#include "area030_04.h"

/* Resets the AREA030 panel scratch state and queues the cue selected
 * by the current sub-state table entry. */
MATCH void func_801E0124(void) {
    FishingState* record;

    FISHING_STATE->bounce_3C.unk_3C = 0;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));

    Area_SelectSceneRecord(*(u16*)(D_801E2ACA + FISHING_STATE->cue_index_06 * 36));

    record        = FISHING_STATE;
    record->flags = (record->flags & ~ACTOR_FLAG_SEMI_TRANSPARENT);

    FISHING_STATE->state_2A = 0;

    FISHING_STATE->counter_48 = 0;
    Actor_SelectScript(0);

    record                = FISHING_STATE;
    record->mode_index_02 = (record->mode_index_02 + 1);
}
