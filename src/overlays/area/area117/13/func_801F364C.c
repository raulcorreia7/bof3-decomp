#include "area117_13.h"

MATCH void func_801F364C(void) {
    if (SYS_TestFlag(D_80144ED0, D_801F463C[TASK(Actor)->param.unk_0B])) {
        TASK(Actor)->timer = 9;
        TASK(Actor)->header.step++;
    }
    func_801F3884(0, 64);
}
