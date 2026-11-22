#include "area118_13.h"

MATCH void func_801F4278(void) {
    u8* flags;

    flags = D_80144ED0;
    if (!SYS_TestFlag(flags, D_801F5198[TASK(Actor)->param.unk_0B])) {
        TASK(Actor)->timer = 9;
        TASK(Actor)->header.step++;
    }
    func_801F4634(TASK(Actor)->param.unk_0B + SYS_TestFlag(flags, D_801F5138[TASK(Actor)->param.unk_0B]) * 4 + 1, 0x40);
    func_801F48E0();
}
