#include "area118_13.h"

MATCH void func_801F3534(void) {
    TASK(Actor)->screen_y -= 0x20;
    if ((s16)TASK(Actor)->screen_y < -0xFF) {
        TASK(Actor)->header.step++;
    }
    func_801F381C(0);
}
