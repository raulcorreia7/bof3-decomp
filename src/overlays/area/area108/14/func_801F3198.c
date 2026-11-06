#include "area108_14.h"

MATCH void func_801F3198(void) {
    AreaSprite* work;
    u8          count;
    u8          tick;

    work = (AreaSprite*)D_801F63EC;
    tick = (work->flags_03 - 1u);
    work->origin_x += work->normal.vx;
    work->origin_y += work->normal.vy;
    work->flags_03 = tick;
    work->origin_z += work->normal.vz;
    count                               = (((AreaSprite*)D_801F63EC)->flags_02 - 1u);
    ((AreaSprite*)D_801F63EC)->flags_02 = count;
    if (!(count & 0xFF)) {
        ((AreaSprite*)D_801F63EC)->flags = 0u;
    }
}
