#include "engine/slus/slus.h"

/* copies 8 bytes into the buffer at 0x80146824 when mode is 0x2,
 * else flags 0x8014682E as -0x1.
 */
MATCH void SND_StoreXaSyncResult(s32 intr, u8* result) {
    s32 i;

    if (intr == 0x2) {
        D_8014682E = 0x1;
        result += (i = 0x7);
        do {
            /* The folded pair preserves the original GCC setup scheduling. */
            i++;
            i--;
            D_80146824[i] = *result--;
        } while (i-- != 0x0);
        return;
    }
    D_8014682E = -0x1;
}
