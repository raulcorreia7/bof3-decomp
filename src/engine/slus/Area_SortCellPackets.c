#include "engine/slus/slus.h"

/* exchange-sorts the g_AreaCellPackets words by their high halfword, swapping
 * each out-of-order pair through the scratchpad word at +0xC.
 */
/* func_80153D34 */
MATCH void Area_SortCellPackets(void) {
    s32 i;
    s32 j;
    u32 current;

    for (i = 0; i < g_AreaCellPacketCount; i++) {
        for (j = i + 1; j < g_AreaCellPacketCount; j++) {
            current = g_AreaCellPackets[i];
            if ((g_AreaCellPackets[j] >> 16) < (current >> 16)) {
                /* FAKE_VOLATILE: retail keeps the store and reload of the scratchpad word; a plain access is optimised away (size 0xA4, not 0xB4). */
                FAKE_VOLATILE(u32, D_1F80000C) = current;
                g_AreaCellPackets[i]           = g_AreaCellPackets[j];
                /* FAKE_VOLATILE: the reload reads the word back from the scratchpad, as retail does. */
                g_AreaCellPackets[j]           = FAKE_VOLATILE(u32, D_1F80000C);
            }
        }
    }
}
