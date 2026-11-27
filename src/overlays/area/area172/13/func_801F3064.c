#include "area172_13.h"

MATCH void func_801F3064(void) {
    u16 screen_x;
    u8  mode;

    screen_x              = SELF(Actor)->screen_x + 0x18;
    SELF(Actor)->screen_x = screen_x;
    func_801F36C0(&SELF(Actor)->pos.x, (s16)screen_x, 7);
    ACTOR_COUNT_DOWN(SELF(Actor), mode, timer);
    if (!(mode & BYTE_MASK)) {
        SELF(Actor)->timer = 64;
        SELF(Actor)->header.mode += 1;
    }
}
