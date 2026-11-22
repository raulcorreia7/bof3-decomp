#include "engine/slus/slus.h"

/* latches the loader status, selecting the error status when the
 * recorded state is negative.
 */
MATCH void CD_OnSeek(void) {
    s32 state;

    state = g_EmiStream.cd_sync_status;
    if (state < 0) {
        state = CD_STATE_SET_SPEED;
    } else {
        state = CD_STATE_READ;
    }
    g_EmiStream.cd_state = state;
}
