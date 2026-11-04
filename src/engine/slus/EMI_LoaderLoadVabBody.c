#include "engine/slus/slus.h"

/* starts the current EMI entry transfer and records either its
 * active-slot state or a terminal loader error before advancing the step.
 */
MATCH void EMI_LoaderLoadVabBody(void) {
    u32 read_cursor;
    u8  entry_index;
    u8  source_index;

    if (EMI_LOADER_STEP == 0) {
        SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
        SsVabClose(D_8014677C[D_80146483].resource_id);
        entry_index = D_80146483;
        if ((s16)SsVabOpenHeadSticky((unsigned char*)D_8014677C[entry_index].source,
                                     D_8014677C[entry_index].resource_id, D_8014677C[entry_index].spu_address) == -1) {
            g_EmiReadStatus  = 2;
            g_EmiStreamState = 0;
            return;
        }

        *(s32*)(((u8*)&EMI_LOADER_STEP + 0x4C + (g_EmiRingSlot * 4))) = -1;
        D_80146486                                                    = 1;
        read_cursor                                                   = g_EmiBytesLeft;
        source_index                                                  = g_EmiNextSlot;
        D_80146478                                                    = read_cursor + 0x800;
        D_80146485                                                    = source_index;
    }

    g_EmiRingStates[g_EmiRingSlot] = 4;
    g_EmiStep += 1;
}
