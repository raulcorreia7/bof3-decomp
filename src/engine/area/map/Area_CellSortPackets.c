#include "engine/slus/slus.h"

/* exchange-sorts the g_AreaCellPackets words by their high halfword, swapping
 * each out-of-order pair through the scratchpad word at +0xC.
 */
/* func_80153D34 */
MATCH void Area_CellSortPackets(void) {
    s32 i;
    s32 j;
    u32 current;

    for (i = 0; i < g_AreaCellPacketCount; i++) {
        for (j = i + 1; j < g_AreaCellPacketCount; j++) {
            current = g_AreaCellPackets[i];
            if ((g_AreaCellPackets[j] >> 16) < (current >> 16)) {
                g_ScratchPad.cells.words[3] = current;
                g_AreaCellPackets[i]        = g_AreaCellPackets[j];
                g_AreaCellPackets[j]        = g_ScratchPad.cells.words[3];
            }
        }
    }
}
