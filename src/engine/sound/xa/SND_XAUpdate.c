#include "engine/slus/slus.h"

/* runs the active state handler, then advances the timer and
 * steps the state machine forward on expiry.
 */
MATCH void SND_XAUpdate(void) {
    s32 temp;
    s8* mode;

    mode = &g_EmiServiceState;
    g_XAStates[*mode]();
    g_XAWaitFrames++;

    if (g_XAStopRequested != 0 && *mode < SND_XA_STATE_PAUSE) {
        g_XAWaitFrames = 0;
        *mode          = SND_XA_STATE_WAIT_SYNC;
    }

    if (g_XAWaitFrames >= 0xB5 && ((g_EmiServiceState = SND_XA_STATE_SEEK, temp = (s16)g_XARetryCount++ < 6, temp == 0) || SND_XAHasCDError() != 0) && g_EmiServiceState < SND_XA_STATE_PAUSE) {
        g_EmiServiceState = SND_XA_STATE_WAIT_SYNC;
    }
}
