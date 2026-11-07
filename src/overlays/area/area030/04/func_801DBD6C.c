#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Draws the AREA030 prompt rows for the current slot and, at the end
 * of the fade, retires or advances the sub-state selected by the work byte. */
MATCH void func_801DBD6C(void) {
    FishingState* work;
    s32           offset;
    u16           cue;
    u8            state;

    work                = FISHING_STATE;
    work->step_timer_09 = (work->step_timer_09 - 1);

    func_801E0ED0(0, 0x4E);
    func_801E0F4C(0x80, 0x5B, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(0xB0, 0x9C);

    work  = FISHING_STATE;
    state = work->saved_index_0B;
    if (state == 1) {
        cue = 0x43;
        func_801E162C(8, work->step_timer_09 * 0x1E + 0x94, cue);
    } else if (state == 2) {
        cue = 0x42;
        func_801E162C(8, work->step_timer_09 * 0x1E + 0x94, cue);
    }

    work = FISHING_STATE;
    if (work->step_timer_09 == 0) {
        state = work->saved_index_0B;
        if (state == 1) {
            work->cue_index_06 = 0;
            work               = FISHING_STATE;
            work->sub_index_03 = 0xC;
        } else if (state == 2) {
            work->sub_index_03 = (work->sub_index_03 + 1);
        }
    }
    func_8014D978();
    func_801E16DC();
}
