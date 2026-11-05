#include "area030_04.h"

/* Advances the AREA030 state byte when the world gate is open,
 * then runs the shared state dispatcher. */
MATCH void func_801D25F0(void) {
    FishingState* record;

    if (func_8014DAEC() != 0u) {
        Actor_SelectScript(3);
        record                   = FISHING_STATE;
        record->handler_index_01 = (record->handler_index_01 + 1);
    }

    func_8014D290();
}
