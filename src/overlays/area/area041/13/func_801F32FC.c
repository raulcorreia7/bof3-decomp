#include "area041_13.h"

MATCH void func_801F32FC(void) {
    TASK(Actor)->timer += 1;
    TASK(Actor)->pos.x.fixed = ((TASK(Actor)->timer & 0x1) * 8) - 0x2B80;
    if (TASK(Actor)->timer >= 8U) {
        TASK(Actor)->timer       = 0;
        TASK(Actor)->pos.x.fixed = -0x2B80;
        TASK(Actor)->header.step += 1;
    }
    func_801F2EFC();
    func_801F3064();
}
