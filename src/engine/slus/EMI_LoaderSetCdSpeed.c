#include "engine/slus/slus.h"

/* syncs the CD reader, sets double-speed mode, and latches ready
 * state 2 when both commands succeed.
 */
MATCH void EMI_LoaderSetCdSpeed(void) {
    u8  param[8];
    u8* result;

    result   = D_80146498;
    param[0] = CdlModeSpeed | CdlModeSize1;
    if (CdSync(1, result) == CdlNoIntr) {
        return;
    }
    if (CdControl(CdlSetmode, param, result) == 0) {
        return;
    }
    D_80146492 = 2;
    D_8014648C = 0;
    D_8014648A = 2;
}
