#include "area030_04.h"

/* Clears the scratch work object's bytes 0x09-0x0B and halfword
 * 0x30, then advances its state byte 0x01. */
/* func_801D2D74 */
MATCH void Fishing_ReelGaugeInit(void) {
    FishingState* record;
    FishingState* retired;

    record                          = SELF(FishingState);
    record->timer                   = 0;
    retired                         = SELF(FishingState);
    record->origin_y                = 0;
    retired->step_index             = 0;
    SELF(FishingState)->saved_index = 0;
    SELF(FishingState)->handler_index += 1;
}
