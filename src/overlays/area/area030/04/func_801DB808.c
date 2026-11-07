#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callees. */

/* Counts the AREA030 prompt timer down while the slot row scrolls,
 * then steps the work state once the timer expires and runs the shared tails. */
MATCH void func_801DB808(void) {
    s32 offset;

    FISHING_STATE->step_timer_09 = (FISHING_STATE->step_timer_09 - 1);

    func_801E0ED0(0, 0x4E);
    func_801E0F4C(0x80, 0x5B, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], 0, FISHING_STATE->step_timer_09);

    if (FISHING_STATE->step_timer_09 == 0) {
        FISHING_STATE->sub_index_03 = (FISHING_STATE->sub_index_03 + 1);
    }
    func_8014D978();
    func_801E16DC();
}
