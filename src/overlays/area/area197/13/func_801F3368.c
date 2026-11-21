#include "area197_13.h"

MATCH s32 func_801F3368(void) {
    AreaDropParticle* drop;
    s32               alive;
    u16               i;
    u8                life;

    alive = 0;
    drop  = MEM_PTR(AreaDropParticle, AREA_DROP_ROWS);
    i     = 0;
    do {
        if (drop->header.active != 0) {
            drop->pos.vx += drop->velocity.vx;
            drop->pos.vy += drop->velocity.vy;
            drop->pos.vz += drop->velocity.vz;
            drop->velocity.vz -= TO_COORD(4);
            if (drop->pos.vz < -TO_COORD(512)) {
                drop->pos.vz      = -TO_COORD(512);
                drop->velocity.vz = -drop->velocity.vz;
            }
            drop->header.shade -= 2;
            life              = drop->header.life - 1;
            drop->header.life = life;
            if (life == 0) {
                drop->header.active = 0;
            }
            func_801F32A4((Actor*)drop);
            alive = 1;
        }
        drop++;
        i++;
    } while (i < AREA_DROP_COUNT);
    return alive;
}
