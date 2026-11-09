#include "engine/slus/slus.h"

/* stops every voice of every live selection effect. */
MATCH void SND_StopAllSequences(void) {
    u8 i;
    u8 j;

    for (i = 0; i < 5; i++) {
        if (g_SelectionFxVoices[i] != -1) {
            for (j = 0; j < 4; j++) {
                SND_StopSequence(i, j);
            }
        }
    }
}
