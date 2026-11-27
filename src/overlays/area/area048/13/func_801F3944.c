#include "area048_13.h"

MATCH s32 func_801F3944(void) {
    func_801F3AE4(0x400, 0x858000, 0x10);
    func_801F3AE4(0xC00, 0x878000, 0x11);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 5U) {
        SELF(Actor)->header.step += 1;
        SELF(Actor)->timer = 0;
    }
}
