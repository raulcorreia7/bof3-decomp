#include "engine/slus/slus.h"

/* selects the CD-read dispatch mode from the latched sync status.
 */
MATCH void CD_OnPause(void) {
    if (g_CdSyncStatus < 0) {
        g_CdState = CD_STATE_PAUSE;
        return;
    }
    g_CdState = CD_STATE_IDLE_END;
    if (D_8014648B & 0x1) {
        g_CdState = CD_STATE_SET_SPEED;
        return;
    }
    if (D_8014648B & 0x2) {
        CdReadyCallback(NULL);
        g_EmiStreamState = 2;
    }
}
