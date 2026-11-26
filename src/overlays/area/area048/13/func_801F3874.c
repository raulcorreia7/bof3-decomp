#include "area048_13.h"

MATCH void func_801F3874(void) {
    u8 timer;

    timer = SELF(Actor)->timer;
    func_801F3AE4(timer << 4, 0x858000, (timer >= 49U) << 4);
    timer = SELF(Actor)->timer;
    func_801F3AE4((timer + 128) << 4, 0x878000, timer >= 49U ? 0x11 : 1);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 65U) {
        SELF(Actor)->header.step += 1;
        SELF(Actor)->timer = 0;
    }
}
