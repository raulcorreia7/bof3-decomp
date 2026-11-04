#include "engine/slus/slus.h"

/* scans the sep table for a claimable voice: the first entry with a
 * bound sep id whose four seq slots report end-of-sequence is written back as
 * (entry index, seq); returns 0 on a claim and 1 when none is free.
 */
MATCH s32 SND_FindFreeFxVoice(u8* out_index, u8* out_seq) {
    s32 i;
    s32 j;
    s16 value;
    s8  sep;

    for (i = 0; (i & BYTE_MASK) == 0; i++) {
        for (j = 0; (u32)(j & BYTE_MASK) < 4U; j++) {
            sep = g_SelectionFxVoices[i & BYTE_MASK];
            if (sep != -1) {
                value = SsIsEos(sep, j & BYTE_MASK);
                if (value != 0) {
                    *out_index = i;
                    *out_seq   = j;
                    return 0;
                }
            }
        }
    }
    return 1;
}
