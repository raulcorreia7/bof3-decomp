#include "area111_13.h"

MATCH void func_801F2CFC(void) {
    u8     remaining;
    Actor* actor;

    func_801F2DA0(&SELF(Actor)->pos.x, (s16)SELF(Actor)->screen_x, (s16)SELF(Actor)->screen_y);
    actor     = SELF(Actor);
    remaining = --actor->timer;
    actor->screen_x += 0x40;
    actor->screen_y += 0x40;
    if (remaining == 0) {
        SELF(Actor)->header.mode++;
    }
}
