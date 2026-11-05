#include "area030_04.h"

/* Ticks the panel animation counter down, redraws the two panel
 * rows, and advances the panel state once the counter reaches zero. */
MATCH void func_801DB738(void) {
    FishingState* record;

    record                = FISHING_STATE;
    record->step_timer_09 = (u8)(record->step_timer_09 - 1);
    func_801E0ED0(0, 0x4E);

    func_801E0F4C((FISHING_STATE->step_timer_09 * 48) + 0x80, 0x5B, g_Actors[D_801E3208].unk_06);

    record = FISHING_STATE;
    if (record->step_timer_09 == 0) {
        record->step_timer_09 = 4;
        record                = FISHING_STATE;
        record->sub_index_03  = (u8)(record->sub_index_03 + 1);
    }

    func_8014D978();
    func_801E16DC();
}
