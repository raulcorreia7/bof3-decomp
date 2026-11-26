#include "area118_13.h"

MATCH void func_801F4340(void) {
    SELF(Actor)->timer--;
    if (SELF(Actor)->timer == 0) {
        SELF(Actor)->header.step++;
    }
    func_801F4634(0, 0x40);
    func_801F4634(SELF(Actor)->param.unk_0B + SYS_TestFlag(D_80144ED0, D_801F5138[SELF(Actor)->param.unk_0B]) * 4 + 1, SELF(Actor)->timer << 3);
    func_801F48E0();
}
