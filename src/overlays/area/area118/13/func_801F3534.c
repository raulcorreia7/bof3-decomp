#include "area118_13.h"

MATCH void func_801F3534(void) {
    SELF(Actor)->screen_y -= 0x20;
    if ((s16)SELF(Actor)->screen_y < -0xFF) {
        SELF(Actor)->header.step++;
    }
    func_801F381C(0);
}
