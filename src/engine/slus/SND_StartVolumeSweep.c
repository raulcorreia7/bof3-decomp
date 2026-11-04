#include "engine/slus/slus.h"

/* starts a volume sweep on the voice from the current level in
 * D_80148FC8 to the target level in D_80148FF8, then records the target as the
 * current level.
 */
MATCH void SND_StartVolumeSweep(s32 voice) {
    u16 index;

    index = voice;
    SsUtAutoVol((s16)index, ((s8*)&D_80148FC8)[index], (s8)D_80148FF8[index], 1);
    ((s8*)&D_80148FC8)[index] = D_80148FF8[index];
}
