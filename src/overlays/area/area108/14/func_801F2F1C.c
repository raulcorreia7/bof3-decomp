#include "area108_14.h"

MATCH void func_801F2F1C(void* sprite) {
    AreaSprite*     work;
    volatile Actor* scratch;

    work           = (AreaSprite*)sprite;
    scratch        = SP_REF(volatile Actor*, 0x44u);
    work->origin.x = scratch->pos.x.fixed;
    work->origin.y = scratch->pos.y.fixed;
    work->origin.z = scratch->pos.z.fixed;
    setVector(&work->normal, RANDOM_MASK(0xFF) - 0x80, RANDOM_MASK(0xFF) - 0x80, RANDOM_MASK(0x7F));
    VectorNormal(&work->normal, &work->normal);
    work->flags     = 1u;
    work->tick      = 0x40u;
    work->stage     = 0u;
    work->half_size = 0u;
    work->count     = 4u;
    work->normal.vz <<= 8;
}
