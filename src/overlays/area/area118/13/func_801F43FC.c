#include "area118_13.h"

MATCH void func_801F43FC(void) {
    if (SYS_TestFlag(D_80144ED0, D_801F5198[TASK(Actor)->param.unk_0B])) {
        TASK(Actor)->timer = 9;
        TASK(Actor)->header.step++;
    }
    func_801F4634(0, 64);
}
