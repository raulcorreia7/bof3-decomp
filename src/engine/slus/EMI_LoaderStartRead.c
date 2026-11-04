#include "engine/slus/slus.h"

/* syncs the CD reader, retries the pending read, and latches progress
 * on success.
 */
MATCH void EMI_LoaderStartRead(void) {
    u8* result;

    result = D_80146498;
    if (CdSync(1, result) != CdlNoIntr) {
        D_8014648C = 0;
        /* Read target is D_80146778 (CdlLOC; see EMI_LdrBeginRead.c); object form
         * regresses bytes. */
        if (CdControl(CdlReadN, result + 0x2E0, NULL) != 0) {
            D_8014648A       = 5;
            g_EmiStreamState = 1;
        }
    }
}
