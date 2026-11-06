#include "area108_14.h"

MATCH void func_801F30FC(void) {
    AreaSprite* work;
    u8          count;

    work           = (AreaSprite*)D_801F63EC;
    count          = (work->flags_02 - 1u);
    work->flags_02 = count;
    work->origin.x += (work->normal.vx * 2);
    work->origin.y += (work->normal.vy * 2);
    work->origin.z += (work->normal.vz * 2);
    work->half_size = (work->half_size + 0x80u);
    if (!(count & BYTE_MASK)) {
        ((AreaSprite*)D_801F63EC)->flags_02 = 0x40u;
        ((AreaSprite*)D_801F63EC)->flags_01 = (((AreaSprite*)D_801F63EC)->flags_01 + 1u);
    }
}
