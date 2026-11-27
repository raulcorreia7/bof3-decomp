#include "engine/slus/slus.h"

/* Returns the index of the first active live pond record with fish id 0x0A inside the player's reach, or -1.
 */
MATCH s8 func_8014DE78(void) {
    Actor* self;
    s32    range;
    s8     i;

    i    = 0;
    self = SELF(Actor);
    for (; i < 34; i++) {
        if (!ACTOR_IN_USE(g_Actors[i])) {
            continue;
        }
        if (!(g_Actors[i].active_flags & ACTOR_ACTIVE_READY)) {
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
        if (range < abs(self->pos.x.fixed - g_Actors[i].pos.x.fixed)) {
            continue;
        }
        if (range < abs(self->pos.y.fixed - g_Actors[i].pos.y.fixed)) {
            continue;
        }
        if (abs(COORD_INT(self->pos.z) - COORD_INT(g_Actors[i].pos.z)) < 769) {
            return i;
        }
    }
    return -1;
}
