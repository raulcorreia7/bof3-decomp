#include "engine/slus/slus.h"

/* selects the CD-read dispatch mode from the latched sync status.
 */
MATCH void CD_OnPause(void) {
    if (g_EmiStream.cd_sync_status < 0) {
        g_EmiStream.cd_state = CD_STATE_PAUSE;
        return;
    }
    g_EmiStream.cd_state = CD_STATE_IDLE_END;
    if (g_EmiStream.unk_3B & 0x1) {
        g_EmiStream.cd_state = CD_STATE_SET_SPEED;
        return;
    }
    if (g_EmiStream.unk_3B & 0x2) {
        CdReadyCallback(NULL);
        g_EmiStream.state = 2;
    }
}
