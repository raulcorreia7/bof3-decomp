#include "engine/slus/slus.h"

/* selects the CD-read completion mode from the latched sync status
 * and clears the retry flag on failure.
 */
MATCH void CD_OnRead(void) {
    u8 mode;

    if (g_CdSyncStatus < 0) {
        g_EmiStreamState = 0;
        mode             = 4;
    } else {
        mode = 8;
    }
    g_CdStep = mode;
}
