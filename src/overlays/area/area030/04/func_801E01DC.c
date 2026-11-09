#include "area030_04.h"

/* Advances the scratchpad step byte when the work object's 0x58 halfword equals the table entry selected by its byte 6. */
MATCH void func_801E01DC(void) {
    FishingState* record;

    record = FISHING_STATE;
    if (record->flags_58 == D_801E2354[record->cue_index_06]) {
        record->mode_index_02 += 1;
    } else {
        Actor_StepAnimLoop();
    }
}
