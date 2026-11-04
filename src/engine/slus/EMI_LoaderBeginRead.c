#include "engine/slus/slus.h"

/* resets EMI transfer counters, converts the current LBA to CdlLOC,
 * and arms the next loader phase.
 */
MATCH void EMI_LoaderBeginRead(void) {
    volatile u8* read_progress;
    s8           state;
    u32          lba;

    read_progress  = &g_EmiStreamState;
    *read_progress = 0;
    lba            = g_EmiSectorCursor;
    D_80146490     = 0;
    CdIntToPos(lba, (CdlLOC*)(&g_EmiStreamState + 0x2E4));
    D_80146492      = 3;
    g_EmiReadStatus = 0;
    state           = D_8014648B;
    D_8014648A      = state == 1 ? 6 : 1;
}
