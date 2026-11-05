#include "area030_04.h"

/* Advances the AREA030 sub-state counter, seeds the battle
 * parameters from the current slot, and enters the next mode. */
MATCH void func_801DAF18(void) {
    u8 counter;

    D_8014419E = 2;
    counter    = D_80144199;
    D_801440B1 = 0;
    D_80144199 = (u8)(counter + 1);

    g_AreaScrollTargetY = *(u32*)(D_801468C0 + D_801E3208 * 152);
    SND_StartDecrescendo(0, 0, 0x64, 8);
    D_80144125 = 7;
    FISHING_STATE->sub_index_03 += 1;
}
