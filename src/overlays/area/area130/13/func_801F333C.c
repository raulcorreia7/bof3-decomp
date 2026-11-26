#include "area130_13.h"

MATCH void func_801F333C(void) {
    u16* cell;
    u8   timer;

    cell = &D_801469EA;
    *cell += 0xF00;
    func_801F3400(SELF(Actor)->screen_x, SELF(Actor)->screen_y, SELF(Actor)->vx, SELF(Actor)->vy);
    ACTOR_COUNT_DOWN(SELF(Actor), timer, timer);
    if (timer == 0) {
        SELF(Actor)->header.mode++;
    }
}
