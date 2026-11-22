#include "area103_13.h"

MATCH void func_801F4F44(void) {
    func_801F5174(TASK(Actor)->timer, 0x80);
    func_801F53F0(TASK(Actor)->timer);
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 8U) {
        TASK(Actor)->header.step += 1;
    }
}
