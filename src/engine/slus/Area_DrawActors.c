#include "engine/slus/slus.h"

/* sorts the active work-record table by its 0x3E key with a
 * descending bubble pass, then points the scratchpad work slot at each record
 * in order and runs the per-record update.
 */
MATCH void Area_DrawActors(void) {
    MATCH_REG(s32, count, "a0"); /* FAKE: retail keeps the record count in a0. */
    s32 i;
    s32 j;
    s32 start;
    MATCH_REG(s32, index, "a2"); /* FAKE: retail keeps the row index in a2. */

    if (g_AreaDrawFlags & AREA_DRAW_SORTED_RECORDS) {
        count = D_8014832C;
        i     = 0;
        if ((s32)(count - 1) > 0) {
            do {
                j     = count - 1;
                index = j & BYTE_MASK;
                if (index >= (i & BYTE_MASK) + 1) {
                    start = (i & BYTE_MASK) + 1;
                    do {
                        if (D_80148214[index]->z.part.integer < D_80148214[index - 1]->z.part.integer) {
                            Area_SwapActors(index, (j - 1) & BYTE_MASK);
                        }
                        j--;
                        index = j & BYTE_MASK;
                    } while (index >= start);
                }
                i++;
                count = D_8014832C;
            } while ((s32)(i & BYTE_MASK) < (count - 1));
        }
        if (D_8014832C != 0) {
            i = 0;
            do {
                SP_REF(Actor*, 0x44) = D_80148214[i & BYTE_MASK];
                i++;
                Area_DrawObjectSprite();
            } while ((u8)i < D_8014832C);
        }
    }
}
