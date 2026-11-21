#include "engine/game/00/game_00.h"

/* func_801BDD58 */
/* Returns whether a point lies within reach of an actor record. */
#ifdef NON_MATCHING
NON_MATCHING u8 Actor_IsInRange(s32 pos_x, s32 pos_y, s16 z, s32 reach, Actor* record) {
    /* FAKE: plain C gives the record t0 and pos_x a0; 46 rows measured without the pins. */
    FAKE_REG(s32, px, "t0");
    FAKE_REG(Actor*, rec, "a0");
    s32 x;
    s32 y;
    s32 dist;
    s32 bound;

    /* FAKE: the entry copy sinks to its reader without this use. */
    px = pos_x;
    FAKE_USE(px);
    rec  = record;
    dist = rec->pos.z.part.integer - z;
    if (dist < 0) {
        dist = -dist;
    }
    reach += rec->voice_flags.scene_flag;
    if (dist > (reach << 7) + 0x100) {
        return 0;
    }
    x     = rec->pos.x.fixed + rec->vx * rec->timer;
    y     = rec->pos.y.fixed + rec->vy * rec->timer;
    bound = (reach + 2) << 15;
    dist  = px - x;
    if (dist < 0) {
        dist = -dist;
    }
    if (dist < bound) {
        dist = pos_y - y;
        if (dist < 0) {
            dist = -dist;
        }
        return dist < bound;
    }
    return 0;
}
#else
INCLUDE_ASM(Actor_IsInRange);
#endif
