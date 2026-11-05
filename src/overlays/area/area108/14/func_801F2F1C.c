#include "area108_14.h"

MATCH void func_801F2F1C(void* sprite) {
    AreaSprite*              work;
    volatile Area108Scratch* scratch;

    work            = (AreaSprite*)sprite;
    scratch         = SP_REF(volatile Area108Scratch*, 0x44u);
    work->origin_x  = scratch->pos_x;
    work->origin_y  = scratch->pos_y;
    work->origin_z  = scratch->pos_z;
    work->normal.vx = (RANDOM_MASK(0xFF)) - 0x80;
    work->normal.vy = (RANDOM_MASK(0xFF)) - 0x80;
    work->normal.vz = RANDOM_MASK(0x7F);
    VectorNormal(&work->normal, &work->normal);
    work->flags     = 1u;
    work->flags_03  = 0x40u;
    work->flags_01  = 0u;
    work->half_size = 0u;
    work->flags_02  = 4u;
    work->normal.vz <<= 8;
}
