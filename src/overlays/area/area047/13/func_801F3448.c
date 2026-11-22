#include "area047_13.h"

MATCH void func_801F3448(void) {
    if (TASK(Actor)->header.step == 0) {
        TASK(Actor)->pos.x.fixed = -0x3900;
        TASK(Actor)->pos.y.fixed = -0x3880;
        TASK(Actor)->pos.z.fixed = -0x7F0;
        TASK(Actor)->header.step += 1;
    }
    func_801F34A0();
}
