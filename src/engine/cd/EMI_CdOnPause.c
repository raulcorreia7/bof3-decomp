#include "engine/slus/slus.h"

/* selects the CD-read dispatch mode from the latched sync status.
 */
MATCH void EMI_CdOnPause(void) {
    if (D_8014648C < 0) {
        D_8014648A = 6;
        return;
    }
    D_8014648A = 8;
    if (D_8014648B & 0x1) {
        D_8014648A = 1;
        return;
    }
    if (D_8014648B & 0x2) {
        CdReadyCallback(NULL);
        g_EmiStreamState = 2;
    }
}
