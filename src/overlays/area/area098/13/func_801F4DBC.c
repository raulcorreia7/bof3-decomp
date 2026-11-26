#include "area098_13.h"

MATCH void func_801F4DBC(FallingSpark* slot) {
    slot->header.active = 1;
    slot->header.life   = 8;
    slot->header.type   = 0;
    slot->header.shade  = 0;
    slot->speed         = 0;
    slot->life_reload   = 0x20;
    slot->pos.vx        = SELF(Actor)->pos.x.fixed + ((RANDOM_MASK(BYTE_MASK)) << 10) - 0x20000;
    slot->pos.vy        = SELF(Actor)->pos.y.fixed;
    slot->pos.vz        = SELF(Actor)->pos.z.fixed + ((RANDOM_MOD(0x300)) << 16);
}
