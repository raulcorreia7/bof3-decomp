#include "area117_13.h"

MATCH void func_801F364C(void) {
    if (SYS_TestFlag(D_80144ED0, D_801F463C[SELF(Actor)->param.unk_0B])) {
        SELF(Actor)->timer = 9;
        SELF(Actor)->header.step++;
    }
    func_801F3884(0, 64);
}
