#include "area117_13.h"

MATCH void func_801F34C8(void) {
    u8* flags;

    flags = D_80144ED0;
    if (!SYS_TestFlag(flags, D_801F463C[SELF(Actor)->param.unk_0B])) {
        SELF(Actor)->timer = 9;
        SELF(Actor)->header.step++;
    }
    func_801F3884(SELF(Actor)->param.unk_0B + SYS_TestFlag(flags, D_801F4640[SELF(Actor)->param.unk_0B]) * 4 + 1, 0x40);
    func_801F3AF8();
}
