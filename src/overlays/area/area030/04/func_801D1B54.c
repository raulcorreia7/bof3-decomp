#include "area030_04.h"

/* Seeds the AREA030 scratchpad record for the next state and advances
 * the state byte. */
MATCH void func_801D1B54(void) {
    FishingState* record;
    u8            value;

    record                   = FISHING_STATE;
    value                    = D_801E320C->unk_00;
    record->pos_x_0C         = 0;
    record->cursor_10        = 0;
    record->unk_1C           = 0;
    record->step_delta_18    = value;
    record->handler_index_01 = (u8)(record->handler_index_01 + 1);
}
