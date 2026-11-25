#include "engine/slus/slus.h"

/* syncs the CD reader and stores the pending result word.
 */
MATCH void SND_XAStateWaitSync(void) {
    s16* base;

    base  = &g_XAWaitFrames;
    *base = 0;
    /* Result buffer is g_XACdResult; aggregate layout unrecovered. */
    if (CdSync(1, (u8*)base + 8) != CdlNoIntr) {
        g_EmiServiceState = SND_XA_STATE_PAUSE;
        *base             = 0;
    }
}
