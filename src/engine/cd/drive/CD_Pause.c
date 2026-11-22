#include "engine/slus/slus.h"

/* pauses the CD reader and flags completion.
 */
MATCH void CD_Pause(void) {
    if (CdSync(1, D_80146498) != CdlNoIntr) {
        g_CdSyncStatus = 0;
        if (CdPause() != 0) {
            g_CdState = CD_STATE_PAUSE_WAIT;
        }
    }
}
