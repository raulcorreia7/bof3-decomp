#include "engine/slus/slus.h"

/* selects the CD-read dispatch mode from the latched sync status.
 */
MATCH void CD_OnPause(void) {
    if (g_CdSyncStatus < 0) {
        g_CdStep = 6;
        return;
    }
    g_CdStep = 8;
    if (D_8014648B & 0x1) {
        g_CdStep = 1;
        return;
    }
    if (D_8014648B & 0x2) {
        CdReadyCallback(NULL);
        g_EmiStreamState = 2;
    }
}
