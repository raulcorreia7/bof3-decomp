#include "area030_04.h"

/* Clears the scratch work object's bytes 0x09-0x0B and halfword
 * 0x30, then advances its state byte 0x01. */
/* func_801D2D74 */
MATCH void Fishing_ReelGaugeInit(void) {
    FishingState* record;
    FishingState* retired;

    record                        = FISHING_STATE;
    record->step_timer_09         = 0;
    retired                       = FISHING_STATE;
    record->origin_y_30           = 0;
    retired->step_index_0A        = 0;
    FISHING_STATE->saved_index_0B = 0;
    FISHING_STATE->handler_index_01 += 1;
}
