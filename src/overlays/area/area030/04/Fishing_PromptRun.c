#include "area030_04.h"

/* When the record pointer left the D_80144124 slot and the state byte is below 4, resets the work area. */
/* func_801D35CC */
MATCH void Fishing_PromptRun(void) {
    FishingState* record;

    record = FISHING_STATE;
    if (((u8*)record != &D_80144124) && (D_80144125 < 4u)) {
        Actor_Clear();
        return;
    }
    g_FishingPromptStates[FISHING_STATE->handler_index_01]();
}
