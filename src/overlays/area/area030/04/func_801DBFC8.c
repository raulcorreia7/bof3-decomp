#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Draws the AREA030 prompt rows for the current slot, arms the cursor
 * and caption rows and, on any pad input, retires the caret and advances the
 * panel step. */
MATCH void func_801DBFC8(void) {
    FishingState* work;
    s32           offset;

    func_801E0ED0(0, 0x4E);
    func_801E0F4C(0x80, 0x5B, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(0xB0, 0x9C);
    func_801E162C(8, 0x94, 0x43);

    if (g_InputPressed != 0) {
        FISHING_STATE->cue_index_06 = 0;
        work                        = FISHING_STATE;
        work->sub_index_03          = (work->sub_index_03 + 1);
    }
    func_8014D978();
    func_801E16DC();
}
