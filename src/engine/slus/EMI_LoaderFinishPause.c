#include "engine/slus/slus.h"

/* selects the CD-read dispatch mode from the latched sync status.
 */
MATCH void EMI_LoaderFinishPause(void) {
    if (D_8014648C < 0) {
        D_8014648A = 6;
        return;
    }
    D_8014648A = 8;
    if (D_8014648B & 1) {
        D_8014648A = 1;
        return;
    }
    if (D_8014648B & 2) {
        CdReadyCallback(NULL);
        g_EmiStreamState = 2;
    }
}
