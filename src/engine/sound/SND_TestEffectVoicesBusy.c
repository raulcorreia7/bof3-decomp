#include "engine/slus/slus.h"

/* returns 1 when no effect voice is free; otherwise returns 0 and writes the first entry with a
 * bound sep id whose seq slot reports end-of-sequence back as (entry index, seq).
 */
MATCH bool SND_TestEffectVoicesBusy(u8* out_index, u8* out_seq) {
    s32 i;
    s32 j;
    s16 value;
    s8  sep;

    for (i = 0; (i & BYTE_MASK) == 0; i++) {
        for (j = 0; (j & BYTE_MASK) < 4U; j++) {
            sep = g_SelectionEffectVoices[i & BYTE_MASK];
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
