#include "engine/slus/slus.h"

/* steps the latched level toward the requested level one step at a time, then latches the final value. The
 * address flows through two pointer locals before the loop pointer; the allocator only keeps retail's second live
 * copy (a2) in that shape.
 */
MATCH void SND_FadeCdVolume(s32 level) {
    u8  target;
    u8* base;
    u8* alias;
    u8* p;
    s32 i;

    target = (u8)level;
    base   = &g_SndCdVolume;
    alias  = base;
    p      = alias;
    i      = 0;
    if (p[i] < target) {
        do {
            SND_SetCdVolume(p[i]);
            p[i] = (u8)(p[i] + 1);
        } while (p[i] < target);
    } else if (target < p[i]) {
        do {
            SND_SetCdVolume(p[i]);
            p[i] = (u8)(p[i] - 1);
        } while (target < p[i]);
    }
    SND_SetCdVolume(g_SndCdVolume);
}
