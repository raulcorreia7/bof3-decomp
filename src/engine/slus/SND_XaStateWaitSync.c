#include "engine/slus/slus.h"

/* syncs the CD reader and stores the pending result word.
 */
MATCH void SND_XaStateWaitSync(void) {
    s16* base;

    base  = &D_8014681C;
    *base = 0;
    /* Result buffer is D_80146824; aggregate layout unrecovered. */
    if (CdSync(1, (u8*)base + 8) != CdlNoIntr) {
        g_EmiServiceState = 6;
        *base             = 0;
    }
}
