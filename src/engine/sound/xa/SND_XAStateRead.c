#include "engine/slus/slus.h"

/* polls CD sync, then issues the filter/read commands.
 */
MATCH void SND_XAStateRead(void) {
    if ((CdSync(1, NULL) != CdlNoIntr) && (CdControl(CdlSetfilter, &g_SndXAFilterFile, NULL) != 0)) {
        g_SndXASyncResult = 0;
        /* Param is the word at 0x80146838 (sibling reaches it as g_SndXACdResult[0x14]);
         * aggregate layout unrecovered. */
        if (CdControl(CdlReadS, &g_SndXAFilterFile + 4, NULL) != 0) {
            g_EmiServiceState = SND_XA_STATE_READ_PROGRESS;
            g_SndXAStateFrame = 0;
        }
    }
    g_SndXAWaitFrames = 0;
}
