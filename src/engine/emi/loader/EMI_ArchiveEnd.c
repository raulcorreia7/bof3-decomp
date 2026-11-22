#include "engine/slus/slus.h"

/* selects the CD pause state and EMI phase 2, then clears its busy flag.
 */
MATCH void EMI_ArchiveEnd(void) {
    g_EmiStream.cd_state = CD_STATE_PAUSE;
    g_EmiStream.state    = 0;
    g_EmiStream.unk_3B   = 2;
}
