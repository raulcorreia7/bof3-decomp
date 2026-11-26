#include "area030_04.h"

/* When the gate pair is clear, dispatches the scratch record byte
 * at +2 through the overlay's jump table; otherwise resets the work area. */
MATCH void func_801D56F4(void) {
    FishingState* record;

    if ((g_SpawnedActors[6].unk_08 != 0) || (g_SpawnedActors[6].header.mode != 0xE)) {
        Actor_Clear();
        return;
    }
    record = SELF(FishingState);
    D_801E1FBC[record->mode_index]();
}
