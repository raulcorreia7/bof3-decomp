#include "engine/slus/slus.h"

/* Polls the pending dispatch timer, else advances the retry counter. */
/* polls the status flag and issues the pending CD command.
 */
MATCH void SND_XAStateReadProgress(void) {
    s32 wrap;
    s8* flag;

    flag = &g_SndXASyncResult;
    if (*flag < 0) {
        g_EmiServiceState = SND_XA_STATE_READ;
        if ((((s16)g_SndXARetryCount++ < 6) == 0) || (SND_XAHasCDError() != 0)) {
            g_EmiServiceState = SND_XA_STATE_WAIT_SYNC;
        }
    } else if (*flag != 0) {
        SND_FadeCDVolume(0x80);
        wrap = g_SndXAStateFrame < 6U;
        g_SndXAStateFrame += 1;
        if (wrap == 0) {
            g_EmiServiceState = SND_XA_STATE_READ_RESULT;
            g_SndXAStateFrame = 0;
            g_SndXAWaitFrames = 0;
            *flag             = 0;
            D_8014682F        = 1;
        }
    }
}
