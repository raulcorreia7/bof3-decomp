#include "game_00.h"

/* nonmatching unmeasured: tried regalloc: the work record lands in t0 while retail copies pos_x to t0 and puts the
 * record in a0; the top-level test stays bnez-to-exit in every if/else spelling (hit=0 then, return 0 then, negated
 * then, >= then, <= then, goto) and GCC threads the small then-block into the branch; hoisting the 0x10 product does
 * not change the sink. resume: a source form that frees a0 for the work record (retail copies pos_x to t0 first) and
 * keeps the top-level test as beqz-to-body. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801BDD58(s32 pos_x, s32 pos_y, s16 z, s32 reach, Actor* record) {
    s32 range;
    s32 limit;
    s32 prod_x;
    s32 dist_x;
    s32 dist_y;
    s32 hit;
    u8  factor;

    dist_y = record->z.part.integer - z;
    if (dist_y < 0) {
        dist_y = -dist_y;
    }
    range = reach + record->state_70.byte;
    if (((range << 7) + 0x100) < dist_y) {
        hit = 0;
    } else {
        factor = record->unk_09;
        prod_x = record->unk_0C * factor;
        dist_x = pos_x - (record->x.fixed + prod_x);
        if (dist_x < 0) {
            dist_x = -dist_x;
        }
        limit = (range + 2) << 0xF;
        if (dist_x < limit) {
            hit = pos_y - (record->y.fixed + record->unk_10 * factor);
            if (hit < 0) {
                hit = -hit;
            }
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
