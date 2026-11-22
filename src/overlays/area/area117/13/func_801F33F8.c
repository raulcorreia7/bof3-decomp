#include "area117_13.h"

MATCH void func_801F33F8(void) {
    TASK(Actor)->param.unk_0B = COORD_INT(TASK(Actor)->pos.x);
    TASK(Actor)->pos.x.fixed  = D_801F4658[TASK(Actor)->param.unk_0B * 2] << 16;
    TASK(Actor)->pos.y.fixed  = D_801F4659[TASK(Actor)->param.unk_0B * 2] << 16;
    if (SYS_TestFlag(D_80144ED0, D_801F463C[TASK(Actor)->param.unk_0B])) {
        TASK(Actor)->header.step++;
        func_801F34C8();
    } else {
        TASK(Actor)->header.step = 3;
        func_801F364C();
    }
}
