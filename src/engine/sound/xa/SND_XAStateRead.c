#include "engine/slus/slus.h"

/* polls CD sync, then issues the filter/read commands.
 */
MATCH void SND_XAStateRead(void) {
    if ((CdSync(1, NULL) != CdlNoIntr) && (CdControl(CdlSetfilter, &g_XAFilter, NULL) != 0)) {
        g_XASyncResult = 0;
        /* Param is the word at 0x80146838 (sibling reaches it as g_XACdResult[0x14]);
         * aggregate layout unrecovered. */
        if (CdControl(CdlReadS, &g_XAFilter + 4, NULL) != 0) {
            g_EmiServiceState = SND_XA_STATE_READ_PROGRESS;
            g_XAStateFrame    = 0;
        }
    }
    g_XAWaitFrames = 0;
}
