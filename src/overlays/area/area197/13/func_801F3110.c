#include "area197_13.h"

MATCH void func_801F3110(u16 start, u16 end, Pos3* from, Pos3* to) {
    SparkParticle* particle;
    u16            slot;

    particle = &((SparkParticle*)AREA_WORK)[start];
    for (slot = start; slot < end; slot++) {
        particle->pos.vx = ((RANDOM_MASK(0xFFF) << 8) % (to->x - from->x)) + from->x;
        particle->pos.vz = ((RANDOM_MASK(0xFFF) << 16) % (to->z - from->z)) + from->z;
        particle->pos.vy = from->y;
        setVector(&particle->velocity, 0, RANDOM_MASK(0xFFF) * 4 + AREA_SPARK_SPEED, 0);
        particle->header.active = 1;
        particle->header.type   = 0;
        particle->header.life   = RANDOM_MASK(0x7) + AREA_SPARK_LIFE_BASE;
        particle->header.shade  = AREA_SPARK_SHADE;
        particle->frame         = RANDOM_MASK(0x7);
        particle++;
    }
}
