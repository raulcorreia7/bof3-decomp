#include "engine/slus/slus.h"

/* syncs the CD reader, retries the pending read, and latches progress
 * on success.
 */
MATCH void CD_Read(void) {
    u8* result;

    result = D_80146498;
    if (CdSync(1, result) != CdlNoIntr) {
        g_CdSyncStatus = 0;
        /* Read target is D_80146778 (CdlLOC; see EMI_ArchiveStart.c); object form
         * regresses bytes. */
        if (CdControl(CdlReadN, result + 0x2E0, NULL) != 0) {
            g_CdState        = CD_STATE_READ_WAIT;
            g_EmiStreamState = 1;
        }
    }
}
