#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801BDD58(s32 pos_x, s32 pos_y, s16 z, s32 reach, Actor* record) {
    s32 range;
    s32 limit;
    s32 prod_x;
    s32 dist_x;
    s32 dist_y;
    s32 hit;
    u8  factor;

    dist_y = COORD_INT(record->pos.z) - z;
    dist_y = ABS(dist_y);
    range  = reach + record->state_70.byte;
    if (((range << 7) + 0x100) < dist_y) {
        hit = 0;
    } else {
        factor = record->timer;
        prod_x = record->vx * factor;
        dist_x = pos_x - (record->pos.x.fixed + prod_x);
        dist_x = ABS(dist_x);
        limit  = (range + 2) << 0xF;
        if (dist_x < limit) {
            hit = pos_y - (record->pos.y.fixed + record->vy * factor);
            hit = ABS(hit);
            hit = hit < limit;
        } else {
            hit = 0;
        }
    }
    return hit;
}
#else
INCLUDE_ASM(func_801BDD58);
#endif
