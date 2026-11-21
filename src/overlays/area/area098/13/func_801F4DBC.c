#include "area098_13.h"

MATCH void func_801F4DBC(FallingSpark* slot) {
    slot->active      = 1;
    slot->life        = 8;
    slot->kind        = 0;
    slot->fade        = 0;
    slot->speed       = 0;
    slot->life_reload = 0x20;
    slot->x           = g_Task->pos.x.fixed + ((RANDOM_MASK(BYTE_MASK)) << 10) - 0x20000;
    slot->y           = g_Task->pos.y.fixed;
    slot->z           = g_Task->pos.z.fixed + ((RANDOM_MOD(0x300)) << 16);
}
