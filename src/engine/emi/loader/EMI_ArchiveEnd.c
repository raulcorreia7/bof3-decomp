#include "engine/slus/slus.h"

/* selects the CD pause state and EMI phase 2, then clears its busy flag.
 */
MATCH void EMI_ArchiveEnd(void) {
    g_CdState        = CD_STATE_PAUSE;
    g_EmiStreamState = 0;
    D_8014648B       = 2;
}
