#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callees. */

/* Draws the AREA030 prompt rows for the current slot, arms the cursor
 * and caption rows, and retires the panel when the confirm bits arrive. */
MATCH void func_801DBEDC(void) {
    s32 offset;

    func_801E0ED0(0, 0x4E);
    func_801E0F4C(0x80, 0x5B, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(0xB0, 0x9C);
    func_801E162C(8, 0x94, 0x42);

    if ((g_InputPressed & (PADRup | PADRdown)) != 0) {
        FISHING_STATE->sub_index_03 = 0xE;
    }
    func_8014D978();
    func_801E16DC();
}
