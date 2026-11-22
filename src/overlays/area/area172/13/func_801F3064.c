#include "area172_13.h"

MATCH void func_801F3064(void) {
    u16 screen_x;
    u8  mode;

    screen_x              = TASK(Actor)->screen_x + 0x18;
    TASK(Actor)->screen_x = screen_x;
    func_801F36C0(&TASK(Actor)->pos.x, (s16)screen_x, 7);
    ACTOR_COUNT_DOWN(TASK(Actor), mode, timer);
    if (!(mode & BYTE_MASK)) {
        TASK(Actor)->timer = 64;
        TASK(Actor)->header.mode += 1;
    }
}
