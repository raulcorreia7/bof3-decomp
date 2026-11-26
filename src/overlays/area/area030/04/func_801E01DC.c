#include "area030_04.h"

/* Advances the scratchpad step byte when the work object's 0x58
 * halfword equals the table entry selected by its byte 6; otherwise runs the
 * shared world update. */
MATCH void func_801E01DC(void) {
    FishingState* record;

    record = SELF(FishingState);
    if (record->flags_58 == D_801E2354[record->cue_index]) {
        record->mode_index += 1;
    } else {
        Script_AnimStepLoop();
    }
}
