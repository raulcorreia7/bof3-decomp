#include "engine/slus/slus.h"

/* latches the last CdSync callback result bytes and marks the async
 * sync status.
 */
MATCH void CD_OnSync(s32 status, u8* result) {
    s32 i;

    result += (i = 7);

    do {
        /* The folded pair preserves the original GCC setup scheduling. */
        i++;
        i--;
        D_80146498[i] = *result--;
    } while (i-- != 0);

    if (status == CdlComplete) {
        g_CdSyncStatus = 1;
    } else {
        g_CdSyncStatus = -1;
    }
}
