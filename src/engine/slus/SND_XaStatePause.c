#include "engine/slus/slus.h"

/* Pauses the CD reader once synced, then clears the dispatch timer. */
/* pauses the CD reader when the status counter expires. */
MATCH void SND_XaStatePause(void) {
    D_8014682E = 0;
    SND_FadeCDVolume(0);
    if ((CdSync(1, NULL) != CdlNoIntr) && (CdPause() != 0)) {
        g_EmiServiceState = SND_XA_STATE_PAUSE_RESULT;
        D_8014681C        = 0;
    }
}
