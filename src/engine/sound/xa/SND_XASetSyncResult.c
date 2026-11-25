#include "engine/slus/slus.h"

/* CD sync callback: keeps the drive result bytes and flags the command complete, else failed. */
MATCH void SND_XASetSyncResult(s32 intr, u8* result) {
    s32 i;

    if (intr == CdlComplete) {
        g_XASyncResult = 0x1;
        result += (i = 0x7);
        do {
            /* The folded pair preserves the original GCC setup scheduling. */
            i++;
            i--;
            g_XACdResult[i] = *result--;
        } while (i-- != 0x0);
        return;
    }
    g_XASyncResult = -0x1;
}
