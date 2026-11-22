#include "area197_13.h"

/* kept: area.h declares this with an empty parameter list, so the definition keeps the promoted form. */
MATCH void func_801F34A0(start, end, from, to) u16 start;
u16        end;
Pos3*      from;
Pos3*      to;
{
    AreaDropParticle* row;
    u16               slot;

    row = &((AreaDropParticle*)AREA_DROP_ROWS)[start];
    for (slot = start; slot < end; slot++) {
        row->pos.vx = ((RANDOM_MASK(0xFFF) << 8) % (to->x - from->x)) + from->x;
        row->pos.vz = ((RANDOM_MASK(0xFFF) << 16) % (to->z - from->z)) + from->z;
        row->pos.vy = from->y;
        setVector(&row->velocity, 0, RANDOM_MASK(0xFFF) * 4 + AREA_DROP_SPEED, 0);
        row->header.active = 1;
        row->header.type   = 0;
        row->header.life   = RANDOM_MASK(0x7) + AREA_SPARK_LIFE_BASE;
        row->header.shade  = AREA_SPARK_SHADE;
        row++;
    }
}
