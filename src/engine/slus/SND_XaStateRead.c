#include "engine/slus/slus.h"

/* polls CD sync, then issues the filter/read commands.
 */
MATCH void SND_XaStateRead(void) {
    if ((CdSync(1, NULL) != CdlNoIntr) && (CdControl(CdlSetfilter, &D_80146834, NULL) != 0)) {
        D_8014682E = 0;
        /* Param is the word at 0x80146838 (sibling reaches it as D_80146824[0x14]);
         * aggregate layout unrecovered. */
        if (CdControl(CdlReadS, &D_80146834 + 4, NULL) != 0) {
            g_EmiServiceState = 4;
            D_8014681E        = 0;
        }
    }
    D_8014681C = 0;
}
