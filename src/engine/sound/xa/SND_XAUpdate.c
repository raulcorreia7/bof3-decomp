#include "engine/slus/slus.h"

/* runs the active state handler, then advances the timer and
 * steps the state machine forward on expiry.
 */
MATCH void SND_XAUpdate(void) {
    s32 temp;
    s8* mode;

    mode = &g_EmiServiceState;
    g_XAStates[*mode]();
    D_8014681C++;

    if (D_8014682C != 0 && *mode < SND_XA_STATE_PAUSE) {
        D_8014681C = 0;
        *mode      = SND_XA_STATE_WAIT_SYNC;
    }

    if (D_8014681C >= 0xB5 && ((g_EmiServiceState = SND_XA_STATE_SEEK, temp = (s16)D_80146820++ < 6, temp == 0) || SND_XAHasCDError() != 0) && g_EmiServiceState < SND_XA_STATE_PAUSE) {
        g_EmiServiceState = SND_XA_STATE_WAIT_SYNC;
    }
}
