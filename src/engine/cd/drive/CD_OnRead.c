#include "engine/slus/slus.h"

/* selects the CD-read completion mode from the latched sync status
 * and clears the retry flag on failure.
 */
MATCH void CD_OnRead(void) {
    u8 mode;

    if (g_EmiStream.cd_sync_status < 0) {
        g_EmiStream.state = 0;
        mode              = CD_STATE_READ;
    } else {
        mode = CD_STATE_IDLE_END;
    }
    g_EmiStream.cd_state = mode;
}
