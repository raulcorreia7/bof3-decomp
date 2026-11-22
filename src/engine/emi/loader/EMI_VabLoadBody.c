#include "engine/slus/slus.h"

/* starts the current EMI entry transfer and records either its
 * active-slot state or a terminal loader error before advancing the step.
 */
MATCH void EMI_VabLoadBody(void) {
    u32 read_cursor;
    u8  entry_index;
    u8  source_index;

    if (EMI_LOADER_STEP == 0) {
        SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
        SsVabClose(g_EmiBanks[D_80146483].vab_id);
        entry_index = D_80146483;
        if (SsVabOpenHeadSticky((unsigned char*)g_EmiBanks[entry_index].vab_header, g_EmiBanks[entry_index].vab_id, g_EmiBanks[entry_index].spu_address) == -1) {
            g_EmiReadStatus  = 2;
            g_EmiStreamState = 0;
            return;
        }

        *(s32*)(((u8*)&EMI_LOADER_STEP + 0x4C + (g_EmiRingSlot * 4))) = -1;
        D_80146486                                                    = 1;
        read_cursor                                                   = g_EmiBytesLeft;
        source_index                                                  = g_EmiNextSlot;
        D_80146478                                                    = read_cursor + EMI_SECTOR_SIZE;
        D_80146485                                                    = source_index;
    }

    g_EmiRingStates[g_EmiRingSlot] = 4;
    g_EmiStep += 1;
}
