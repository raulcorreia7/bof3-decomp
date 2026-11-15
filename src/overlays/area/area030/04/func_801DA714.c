#include "area030_04.h"

/* When the AREA030 work object's 0x58 halfword is 6, advances the
 * world phase and resets the work-object bytes for the next state. */
MATCH void func_801DA714(void) {
    FishingState* record;

    Actor_StepAnimLoop();
    record = FISHING_STATE;
    if (record->flags_58 == 6) {
        g_SpawnedActors[0].header.mode = (g_SpawnedActors[0].header.mode + 1);
        record->saved_index_0B         = 0;
        FISHING_STATE->counter_07      = 0;
        FISHING_STATE->sub_index_03    = 3;
    }
}
