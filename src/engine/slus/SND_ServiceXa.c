#include "engine/slus/slus.h"

/* runs the active state handler, then advances the timer and
 * steps the state machine forward on expiry.
 */
MATCH void SND_ServiceXa(void) {
    s32 temp;
    s8* mode;

    mode = &g_EmiServiceState;
    ((void (*)(void))g_XaStateFuncs[*mode])();
    D_8014681C++;

    if (D_8014682C != 0 && *mode < 6) {
        D_8014681C = 0;
        *mode      = 8;
    }

    if (D_8014681C >= 0xB5 &&
        ((g_EmiServiceState = 1, temp = (s16)D_80146820++ < 6, temp == 0) || SND_HasXaCdError() != 0) &&
        g_EmiServiceState < 6) {
        g_EmiServiceState = 8;
    }
}
