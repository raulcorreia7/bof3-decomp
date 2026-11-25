#include "engine/slus/slus.h"

/* syncs the CD reader, sets the read mode, then seeks while idle.
 */
MATCH void SND_XAStateSeek(void) {
    u8 mode;

    mode = CdlModeSpeed | CdlModeRT | CdlModeSF;
    if ((CdSync(1, NULL) != CdlNoIntr) && (CdControl(CdlSetmode, &mode, g_XACdResult) != 0)) {
        g_XASyncResult = 0;
        /* Seek param is the word at 0x80146838 (sibling reaches it as g_XAFilter +
         * 4); aggregate layout unrecovered. */
        if (CdSeekP(&g_XACdResult[0x14]) != 0) {
            g_EmiServiceState = SND_XA_STATE_SEEK_RESULT;
            D_80146832        = 0;
        }
    }
}
