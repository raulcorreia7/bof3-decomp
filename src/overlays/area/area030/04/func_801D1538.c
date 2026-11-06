#include "area030_04.h"

/* Selects the AREA030 scratch mode bytes from the world state:
 * mode 1 clears the flag, otherwise a low world halfword sets it; either
 * way the follow byte is cleared. */
MATCH void func_801D1538(void) {
    FishingState* spike;

    if (D_80145E92[0] == 1) {
        spike                = FISHING_STATE;
        spike->mode_index_02 = 0;
    } else {
        u8 bit = 1;

        if (g_AreaTargetCellY >= 0x38) {
            return;
        }
        spike                = FISHING_STATE;
        spike->mode_index_02 = bit;
    }

    spike               = FISHING_STATE;
    spike->sub_index_03 = 0;
}
