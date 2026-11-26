#include "area077_14.h"

MATCH void func_801F41B4(void) {
    AreaSlot* slot = (AreaSlot*)AREA_WORK;
    u8        i;

    D_800E5500 = 0;
    D_800E5502 = 0;
    for (i = 0; i < AREA_SLOT_COUNT; i++, slot++) {
        slot->pos.x = SELF(Actor)->pos.x.fixed;
        slot->pos.y = SELF(Actor)->pos.y.fixed;
        slot->pos.z = SELF(Actor)->pos.z.fixed;
        slot->angle = 0;
    }
}
