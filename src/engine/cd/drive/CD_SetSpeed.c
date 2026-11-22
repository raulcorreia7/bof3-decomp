#include "engine/slus/slus.h"

/* syncs the CD reader, sets double-speed mode, and latches ready
 * state 2 when both commands succeed.
 */
MATCH void CD_SetSpeed(void) {
    u8  param[8];
    u8* result;

    result   = g_EmiStream.sync_result;
    param[0] = CdlModeSpeed | CdlModeSize1;
    if (CdSync(1, result) == CdlNoIntr) {
        return;
    }
    if (CdControl(CdlSetmode, param, result) == 0) {
        return;
    }
    g_EmiStream.seek_retries   = 2;
    g_EmiStream.cd_sync_status = 0;
    g_EmiStream.cd_state       = CD_STATE_SEEK;
}
