#include "engine/slus/slus.h"

/* steps the status counter and issues the pending CD command.
 */
MATCH void SND_XAStatePauseResult(void) {
    s8* flag;

    flag = &g_XASyncResult;
    if (*flag < 0) {
        g_EmiServiceState = SND_XA_STATE_PAUSE;
        if ((((s16)g_XARetryCount++ < 6) == 0) || (SND_XAHasCDError() != 0)) {
            g_EmiServiceState = SND_XA_STATE_WAIT_SYNC;
        }
    } else if (*flag != 0) {
        D_8014682F        = 2;
        g_EmiServiceState = SND_XA_STATE_IDLE;
        g_XAWaitFrames    = 0;
        *flag             = 0;
        g_EmiStreamState  = 3;
        CdSyncCallback(0);
    }
}
