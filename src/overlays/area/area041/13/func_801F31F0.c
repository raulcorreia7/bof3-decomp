#include "area041_13.h"

MATCH void func_801F31F0(void) {
    if (SYS_TestFlag(D_80144EA0, 6)) {
        SELF(Actor)->header.step = 6;
        SELF(Actor)->pos.x.fixed = -0x2940;
    } else {
        SELF(Actor)->header.step += 1;
        SELF(Actor)->pos.x.fixed = -0x2B80;
    }
    SELF(Actor)->pos.y.fixed      = -0x31C0;
    COORD_INT(SELF(Actor)->pos.z) = -0x80;
    func_801F2EFC();
    func_801F3064();
}
