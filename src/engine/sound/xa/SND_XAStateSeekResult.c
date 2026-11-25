#include "engine/slus/slus.h"

/* steps the pending dispatch timer, else arms the next mode.
 */

MATCH void SND_XAStateSeekResult(void) {
    if (g_SndXASyncResult < 0) {
        g_EmiServiceState = SND_XA_STATE_SEEK;
        if ((((s16)g_SndXARetryCount++ < 6) == 0) || (SND_XAHasCDError() != 0)) {
            g_EmiServiceState = SND_XA_STATE_WAIT_SYNC;
        }
    } else if (g_SndXASyncResult != 0) {
        g_EmiServiceState = SND_XA_STATE_READ;
        D_80146832        = 1;
        g_SndXAWaitFrames = 0;
    }
}
