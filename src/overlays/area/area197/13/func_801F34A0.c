/* The shared area.h gives this symbol no arguments; this image's function reads four. */
#define func_801F34A0 Area_SharedVoidProto
#include "area197_13.h"
#undef func_801F34A0

MATCH void func_801F34A0(u16 start, u16 end, Pos3* from, Pos3* to) {
    AreaDropParticle* particle;
    u16               slot;

    particle = &((AreaDropParticle*)AREA_DROP_ROWS)[start];
    for (slot = start; slot < end; slot++) {
        particle->pos.vx = ((RANDOM_MASK(0xFFF) << 8) % (to->x - from->x)) + from->x;
        particle->pos.vz = ((RANDOM_MASK(0xFFF) << 16) % (to->z - from->z)) + from->z;
        particle->pos.vy = from->y;
        setVector(&particle->velocity, 0, RANDOM_MASK(0xFFF) * 4 + AREA_DROP_SPEED, 0);
        particle->header.active = 1;
        particle->header.type   = 0;
        particle->header.life   = RANDOM_MASK(0x7) + AREA_SPARK_LIFE_BASE;
        particle->header.shade  = AREA_SPARK_SHADE;
        particle++;
    }
}
