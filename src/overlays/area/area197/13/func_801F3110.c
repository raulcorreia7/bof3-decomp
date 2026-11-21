#include "area197_13.h"

MATCH void func_801F3110(u16 start, u16 end, Pos3* from, Pos3* to) {
    SparkParticle* row;
    u16            slot;

    row = &((SparkParticle*)AREA_WORK)[start];
    for (slot = start; slot < end; slot++) {
        row->pos.vx        = ((RANDOM_MASK(0xFFF) << 8) % (to->x - from->x)) + from->x;
        row->pos.vz        = ((RANDOM_MASK(0xFFF) << 16) % (to->z - from->z)) + from->z;
        row->pos.vy        = from->y;
        row->velocity.vx   = 0;
        row->velocity.vy   = RANDOM_MASK(0xFFF) * 4 + AREA_SPARK_SPEED;
        row->velocity.vz   = 0;
        row->header.active = 1;
        row->header.type   = 0;
        row->header.life   = RANDOM_MASK(0x7) + AREA_SPARK_LIFE_BASE;
        row->header.shade  = AREA_SPARK_SHADE;
        row->frame         = RANDOM_MASK(0x7);
        row++;
    }
}
