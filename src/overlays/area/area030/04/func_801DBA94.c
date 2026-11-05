#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Scrolls the AREA030 prompt rows down with the timer and advances
 * the panel step once the timer expires. */
MATCH void func_801DBA94(void) {
    FishingState* work;
    FishingState* state;
    s32           offset;

    work                = FISHING_STATE;
    work->step_timer_09 = (work->step_timer_09 - 1);

    func_801E0ED0(0, 0x4E);
    func_801E0F4C(0x80, 0x5B, D_8014688E[D_801E3208 * 0x98]);

    offset = D_801E3208 * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    func_801E1320(0xB0, FISHING_STATE->step_timer_09 * 0x1E + 0x9C);
    func_801E1C7C();

    state = FISHING_STATE;
    if (state->step_timer_09 == 0) {
        state->sub_index_03 = (state->sub_index_03 + 1);
    }
    func_8014D978();
    func_801E16DC();
}
