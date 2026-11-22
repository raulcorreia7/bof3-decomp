#include "engine/slus/slus.h"

/* latches the loader status, selecting the error status when the
 * recorded state is negative.
 */
MATCH void CD_OnSeek(void) {
    s32 state;

    state = g_CdSyncStatus;
    if (state < 0) {
        state = 1;
    } else {
        state = 4;
    }
    g_CdStep = state;
}
