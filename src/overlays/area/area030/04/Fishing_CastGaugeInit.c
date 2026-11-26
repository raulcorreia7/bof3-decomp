#include "area030_04.h"

/* Seeds the AREA030 scratchpad record for the next state and advances
 * the state byte. */
/* func_801D1B54 */
MATCH void Fishing_CastGaugeInit(void) {
    FishingState* record;
    u8            value;

    record                = SELF(FishingState);
    value                 = g_FishingRodRow->cast_power_speed;
    record->pos_x         = 0;
    record->cursor_10     = 0;
    record->unk_1C        = 0;
    record->step_delta    = value;
    record->handler_index = (record->handler_index + 1);
}
