#include "area130_13.h"

MATCH void func_801F3284(void) {
    u16* cell;
    u8   timer;

    cell = &D_801469EA;
    *cell += 0xF00;
    TASK(Actor)->vx += 15;
    TASK(Actor)->vy += 10;
    func_801F3400(TASK(Actor)->screen_x, TASK(Actor)->screen_y, TASK(Actor)->vx, TASK(Actor)->vy);
    ACTOR_COUNT_DOWN(TASK(Actor), timer, timer);
    if (timer == 0) {
        TASK(Actor)->timer = 60;
        TASK(Actor)->header.mode++;
    }
}
