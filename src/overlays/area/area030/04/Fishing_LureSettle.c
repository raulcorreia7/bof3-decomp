#include "area030_04.h"

/* Advances the AREA030 state byte when the world gate is open,
 * then runs the shared state dispatcher. */
/* func_801D25F0 */
MATCH void Fishing_LureSettle(void) {
    FishingState* record;

    if (Script_AnimStepOnce() != 0u) {
        Script_Select(3);
        record                = SELF(FishingState);
        record->handler_index = (record->handler_index + 1);
    }

    Area_AddGridActor();
}
