#include "area197_13.h"

MATCH s32 func_801F3368(void) {
    AreaDropRow* drop;
    s32          alive;
    u16          i;
    u8           life;

    alive = 0;
    drop  = MEM_PTR(AreaDropRow, AREA_DROP_ROWS);
    i     = 0;
    do {
        if (drop->active != 0) {
            drop->pos.x += drop->vx;
            drop->pos.y += drop->vy;
            drop->pos.z += drop->vz;
            drop->vz -= TO_COORD(4);
            if (drop->pos.z < -TO_COORD(512)) {
                drop->pos.z = -TO_COORD(512);
                drop->vz    = -drop->vz;
            }
            drop->shade -= 2;
            life       = drop->life - 1;
            drop->life = life;
            if (life == 0) {
                drop->active = 0;
            }
            func_801F32A4((Actor*)drop);
            alive = 1;
        }
        drop++;
        i++;
    } while (i < AREA_DROP_COUNT);
    return alive;
}
