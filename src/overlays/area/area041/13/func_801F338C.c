#include "area041_13.h"

MATCH void func_801F338C(void) {
    if (SYS_TestFlag(D_80144EA0, 6)) {
        Actor* a = SELF(Actor);
        s32    x = a->pos.x.fixed;

        a->timer       = 0;
        a->pos.x.fixed = x + 0x40;
        SELF(Actor)->header.step++;
    }
    func_801F2EFC();
    func_801F3064();
}
