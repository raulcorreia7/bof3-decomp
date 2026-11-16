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
        row->pos.x  = ((RANDOM_MASK(0xFFF) << 8) % (to->x - from->x)) + from->x;
        row->pos.z  = ((RANDOM_MASK(0xFFF) << 16) % (to->z - from->z)) + from->z;
        row->pos.y  = from->y;
        row->vx     = 0;
        row->vy     = RANDOM_MASK(0xFFF) * 4 + AREA_DROP_SPEED;
        row->vz     = 0;
        row->active = 1;
        row->unk_01 = 0;
        row->life   = RANDOM_MASK(0x7) + AREA_SPARK_LIFE_BASE;
        row->shade  = AREA_SPARK_SHADE;
        row++;
    }
}
