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

    for (i = 0; (i & 0xFF) == 0; i++) {
        for (j = 0; (j & 0xFF) < 4U; j++) {
            sep = g_SelectionFxVoices[i & 0xFF];
            if (sep != -1) {
                value = SsIsEos(sep, j & 0xFF);
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
