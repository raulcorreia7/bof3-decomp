#include "engine/slus/slus.h"

/* resets EMI transfer counters, converts the current LBA to CdlLOC,
 * and arms the next loader phase.
 */
MATCH void EMI_ArchiveStart(void) {
    volatile u8* read_progress;
    s8           state;
    u32          lba;

    read_progress         = &g_EmiStreamState;
    *read_progress        = 0;
    lba                   = g_EmiSectorCursor;
    g_EmiStreamIdleFrames = 0;
    CdIntToPos(lba, (CdlLOC*)(&g_EmiStreamState + 0x2E4));
    g_EmiSeekRetries = 3;
    g_EmiReadStatus  = 0;
    state            = D_8014648B;
    g_CdState        = state == 1 ? CD_STATE_PAUSE : CD_STATE_SET_SPEED;
}
