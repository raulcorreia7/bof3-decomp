#include "area030_04.h"

/* When the AREA030 work object's 0x58 halfword is 6, advances the
 * world phase and resets the work-object bytes for the next state. */
MATCH void func_801DA714(void) {
    FishingState* record;

    Script_AnimStepLoop();
    record = SELF(FishingState);
    if (record->flags_58 == 6) {
        g_SpawnedActors[0].header.mode = (g_SpawnedActors[0].header.mode + 1);
        record->saved_index            = 0;
        SELF(FishingState)->counter_07 = 0;
        SELF(FishingState)->sub_index  = 3;
    }
}
