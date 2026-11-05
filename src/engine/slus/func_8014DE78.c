#include "engine/slus/slus.h"

/* Returns the index of the first active live pond record with fish id 0x0A inside the player's reach, or -1.
 */
/* nonmatching unmeasured: tried other - self distance order; split dist locals; range reuse; ternary abs; row pointer.
 * resume: a form that writes each distance into the self-field register. */
#ifdef NON_MATCHING
NON_MATCHING s8 func_8014DE78(void) {
    Actor* self;
    s32    range;
    s32    dist;
    s8     i;

    i    = 0;
    self = g_Task;
    for (; i < 34; i++) {
        if (!ACTOR_IN_USE(g_Actors[i])) {
            continue;
        }
        if (!(g_Actors[i].flags_24 & ACTOR_FLAG_ACTIVE)) {
            continue;
        }
        if (g_Actors[i].unk_06 != 0xA) {
            continue;
        }
        if (&g_Actors[i] == (Actor*)self) {
            continue;
        }
        if (g_Actors[i].range_54.table[3] & 0x10) {
            continue;
        }
        range = (s8)g_Actors[i].range_54.table[2] << 15;
        dist  = g_Actors[i].x.fixed - self->x.fixed;
        if (dist < 0) {
            dist = -dist;
        }
        if (range < dist) {
            continue;
        }
        dist = g_Actors[i].y.fixed - self->y.fixed;
        if (dist < 0) {
            dist = -dist;
        }
        if (range < dist) {
            continue;
        }
        range = self->depth.part.integer;
        dist  = range - g_Actors[i].depth.part.integer;
        if (dist < 0) {
            dist = -dist;
        }
        if (dist < 769) {
            return i;
        }
    }
    return -1;
}
#else
INCLUDE_ASM(func_8014DE78);
#endif
