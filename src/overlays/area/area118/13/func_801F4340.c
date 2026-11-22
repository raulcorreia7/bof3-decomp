#include "area118_13.h"

MATCH void func_801F4340(void) {
    TASK(Actor)->timer--;
    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->header.step++;
    }
    func_801F4634(0, 0x40);
    func_801F4634(TASK(Actor)->param.unk_0B + SYS_TestFlag(D_80144ED0, D_801F5138[TASK(Actor)->param.unk_0B]) * 4 + 1, TASK(Actor)->timer << 3);
    func_801F48E0();
}
