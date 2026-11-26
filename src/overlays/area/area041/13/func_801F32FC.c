#include "area041_13.h"

MATCH void func_801F32FC(void) {
    SELF(Actor)->timer += 1;
    SELF(Actor)->pos.x.fixed = ((SELF(Actor)->timer & 0x1) * 8) - 0x2B80;
    if (SELF(Actor)->timer >= 8U) {
        SELF(Actor)->timer       = 0;
        SELF(Actor)->pos.x.fixed = -0x2B80;
        SELF(Actor)->header.step += 1;
    }
    func_801F2EFC();
    func_801F3064();
}
