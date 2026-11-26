#include "engine/slus/slus.h"

/* Pauses the CD reader once synced, then clears the dispatch timer. */
/* pauses the CD reader when the status counter expires.
 */
MATCH void SND_XAStatePause(void) {
    g_SndXASyncResult = 0;
    SND_FadeCDVolume(0);
    if ((CdSync(1, NULL) != CdlNoIntr) && (CdPause() != 0)) {
        g_EmiServiceState = SND_XA_STATE_PAUSE_RESULT;
        g_SndXAWaitFrames = 0;
    }
}
