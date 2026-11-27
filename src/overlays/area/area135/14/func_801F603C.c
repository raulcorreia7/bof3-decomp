#include "area135_14.h"

/* Actor_IsInRange without the height test, on the party row's record and the task's reach. */
MATCH s32 func_801F603C(s32 x, s32 y) {
    u8  timer;
    s32 step_x;
    s32 step_y;
    s32 dx;
    s32 dy;
    s32 range;

    timer  = g_PartyActors[3].timer;
    step_x = g_PartyActors[3].vx * timer;
    step_y = g_PartyActors[3].vy * timer;
    dx     = abs(x - (g_PartyActors[3].pos.x.fixed + step_x));
    dy     = y - (g_PartyActors[3].pos.y.fixed + step_y);
    range  = (SELF(Actor)->voice_flags.scene_flag + g_PartyActors[3].voice_flags.scene_flag + 2) << 15;
    if (dx < range) {
        if (abs(dy) < range) {
            return 1;
        }
    }
    return 0;
}
