#include "area030_04.h"

/* When the record pointer left the D_80144124 slot and the state
 * byte is below 4, resets the work area; otherwise dispatches the scratch
 * record byte at +1 through the overlay's jump table. */
/* func_801D35CC */
MATCH void Fishing_PromptRun(void) {
    FishingState* record;

    record = SELF(FishingState);
    if (((u8*)record != &g_SpawnedActors[3].header.flags) && (g_SpawnedActors[3].header.mode < 4u)) {
        Actor_Clear();
        return;
    }
    g_FishingPromptSteps[SELF(FishingState)->handler_index]();
}
