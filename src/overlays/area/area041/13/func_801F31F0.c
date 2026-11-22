#include "area041_13.h"

MATCH void func_801F31F0(void) {
    if (SYS_TestFlag(D_80144EA0, 6)) {
        TASK(Actor)->header.step = 6;
        TASK(Actor)->pos.x.fixed = -0x2940;
    } else {
        TASK(Actor)->header.step += 1;
        TASK(Actor)->pos.x.fixed = -0x2B80;
    }
    TASK(Actor)->pos.y.fixed      = -0x31C0;
    COORD_INT(TASK(Actor)->pos.z) = -0x80;
    func_801F2EFC();
    func_801F3064();
}
