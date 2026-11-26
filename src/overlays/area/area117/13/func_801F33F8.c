#include "area117_13.h"

MATCH void func_801F33F8(void) {
    SELF(Actor)->param.unk_0B = COORD_INT(SELF(Actor)->pos.x);
    SELF(Actor)->pos.x.fixed  = D_801F4658[SELF(Actor)->param.unk_0B * 2] << 16;
    SELF(Actor)->pos.y.fixed  = D_801F4659[SELF(Actor)->param.unk_0B * 2] << 16;
    if (SYS_TestFlag(D_80144ED0, D_801F463C[SELF(Actor)->param.unk_0B])) {
        SELF(Actor)->header.step++;
        func_801F34C8();
    } else {
        SELF(Actor)->header.step = 3;
        func_801F364C();
    }
}
