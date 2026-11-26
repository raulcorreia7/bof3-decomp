#include "area103_13.h"

MATCH void func_801F4F44(void) {
    func_801F5174(SELF(Actor)->timer, 0x80);
    func_801F53F0(SELF(Actor)->timer);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 8U) {
        SELF(Actor)->header.step += 1;
    }
}
