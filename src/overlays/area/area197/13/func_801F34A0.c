#include "area197_13.h"

MATCH void func_801F34A0(start, end, from, to) u16 start;
u16        end;
Point3l*   from;
Point3l*   to;
{
    AreaDropRow* row;
    u16          slot;

    row = &((AreaDropRow*)AREA_DROP_ROWS)[start];
    for (slot = start; slot < end; slot++) {
        row->pos.x  = ((RANDOM_MASK(0xFFF) << 8) % (to->x - from->x)) + from->x;
        row->pos.z  = ((RANDOM_MASK(0xFFF) << 16) % (to->z - from->z)) + from->z;
        row->pos.y  = from->y;
        row->vx     = 0;
        row->vy     = RANDOM_MASK(0xFFF) * 4 + 0x2000;
        row->vz     = 0;
        row->active = 1;
        row->pad_01 = 0;
        row->life   = RANDOM_MASK(0x7) + 0x18;
        row->shade  = 0x48;
        row++;
    }
}
