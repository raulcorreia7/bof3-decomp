#include "engine/slus/slus.h"

/* syncs the CD reader, retries the pending read, and latches progress
 * on success.
 */
MATCH void CD_Read(void) {
    u8* result;

    result = g_EmiStream.sync_result;
    if (CdSync(1, result) != CdlNoIntr) {
        g_EmiStream.cd_sync_status = 0;
        /* Read target is D_80146778 (CdlLOC; see EMI_ArchiveStart.c); object form
         * regresses bytes. */
        if (CdControl(CdlReadN, result + 0x2E0, NULL) != 0) {
            g_EmiStream.cd_state = CD_STATE_READ_WAIT;
            g_EmiStream.state    = 1;
        }
    }
}
