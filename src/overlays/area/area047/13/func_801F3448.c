#include "area047_13.h"

MATCH void func_801F3448(void) {
    if (SELF(Actor)->header.step == 0) {
        SELF(Actor)->pos.x.fixed = -0x3900;
        SELF(Actor)->pos.y.fixed = -0x3880;
        SELF(Actor)->pos.z.fixed = -0x7F0;
        SELF(Actor)->header.step += 1;
    }
    func_801F34A0();
}
