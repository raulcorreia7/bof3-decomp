#include "area030_04.h"

/* When the gate pair is clear, dispatches the scratch record byte
 * at +2 through the overlay's jump table; otherwise resets the work area. */
MATCH void func_801D56F4(void) {
    FishingState* record;

    if ((D_80144288 != 0) || (D_80144281 != 0xE)) {
        Actor_Clear();
        return;
    }
    record = FISHING_STATE;
    D_801E1FBC[record->mode_index_02]();
}
