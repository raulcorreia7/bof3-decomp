#include "engine/slus/slus.h"

/* pauses the CD reader and flags completion.
 */
MATCH void CD_Pause(void) {
    if (CdSync(1, g_EmiStream.sync_result) != CdlNoIntr) {
        g_EmiStream.cd_sync_status = 0;
        if (CdPause() != 0) {
            g_EmiStream.cd_state = CD_STATE_PAUSE_WAIT;
        }
    }
}
