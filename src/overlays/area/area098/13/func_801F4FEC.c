#include "area098_13.h"

MATCH void func_801F4FEC(AreaBurstSlot* slot) {
    u8 life;

    if (D_801F6514 == 0) {
        D_801F6514 = 1;
    }
    life       = slot->life - 1;
    slot->life = life;
    slot->speed += 0x400;
    slot->distance += slot->speed;
    slot->fade -= 8;
    if (life == 0) {
        slot->active = 0;
    }
}
