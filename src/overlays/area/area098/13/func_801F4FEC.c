#include "area098_13.h"

MATCH void func_801F4FEC(FallingSpark* slot) {
    u8 life;

    if (D_801F6514 == 0) {
        D_801F6514 = 1;
    }
    life              = slot->header.life - 1;
    slot->header.life = life;
    slot->speed += 0x400;
    slot->pos.vy += slot->speed;
    slot->header.shade -= 8;
    if (life == 0) {
        slot->header.active = 0;
    }
}
