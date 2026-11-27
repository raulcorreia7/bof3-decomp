#include "area117_13.h"

MATCH void func_801F3590(void) {
    SELF(Actor)->timer--;
    if (SELF(Actor)->timer == 0) {
        SELF(Actor)->header.step++;
    }
    func_801F3884(0, 0x40);
    func_801F3884(SELF(Actor)->param.unk_0B + SYS_TestFlag(D_80144ED0, D_801F4640[SELF(Actor)->param.unk_0B]) * 4 + 1, SELF(Actor)->timer << 3);
    func_801F3AF8();
}
