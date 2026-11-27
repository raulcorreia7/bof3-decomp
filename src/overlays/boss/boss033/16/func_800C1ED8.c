#include "boss033_16.h"

MATCH void func_800C1ED8(void) {
    Actor* work;

    work          = SELF(Actor);
    work->gravity = work->pos.z.fixed + 0x4000000;
    Script_Select(2);
    SELF(Actor)->param.unk_0B = 0x10;
    SELF(Actor)->header.step++;
}
