#include "engine/slus/slus.h"

/* Pauses the CD reader once synced, then clears the dispatch timer. */
/* pauses the CD reader when the status counter expires.
 */
MATCH void SND_XaStatePause(void) {
    D_8014682E = 0;
    SND_FadeCdVolume(0);
    if ((CdSync(1, NULL) != CdlNoIntr) && (CdPause() != 0)) {
        g_EmiServiceState = 7;
        D_8014681C        = 0;
    }
}
