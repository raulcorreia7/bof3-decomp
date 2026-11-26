#include "area120_13.h"

MATCH void func_801F2CB4(void) {
    s16 timer;

    func_801F3630();
    func_801F3630();
    func_801F3630();
    func_801F3630();
    func_801F36B0();
    timer               = SELF(Actor)->unk_32 - 1;
    SELF(Actor)->unk_32 = timer;
    if (timer == 0) {
        SELF(Actor)->unk_06 = 1;
        SELF(Actor)->unk_32 = 0x3C;
        SELF(Actor)->header.mode++;
    }
}
