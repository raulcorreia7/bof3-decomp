#include "engine/slus/slus.h"

/* syncs the CD reader, sets the read mode, then seeks while idle.
 */
MATCH void SND_XaStateSeek(void) {
    u8 mode;

    mode = CdlModeSpeed | CdlModeRT | CdlModeSF;
    if ((CdSync(1, NULL) != CdlNoIntr) && (CdControl(CdlSetmode, &mode, D_80146824) != 0)) {
        D_8014682E = 0;
        /* Seek param is the word at 0x80146838 (sibling reaches it as D_80146834 +
         * 4); aggregate layout unrecovered. */
        if (CdSeekP(&D_80146824[0x14]) != 0) {
            g_EmiServiceState = 2;
            D_80146832        = 0;
        }
    }
}
