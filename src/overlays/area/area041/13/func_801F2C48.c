#include "area041_13.h"

MATCH void func_801F2C48(void) {
    u8 idx;

    TASK(Actor)->param.unk_0B = TASK(Actor)->pos.x.part.integer;
    idx                       = TASK(Actor)->param.unk_0B;
    if (SYS_TestFlag(g_SceneFlagRows[D_801F42CC[idx]], D_801F42D0[idx])) {
        TASK(Actor)->header.step = 3;
        TASK(Actor)->pos.y.fixed = D_801F42C8[TASK(Actor)->param.unk_0B] + 2;
    } else {
        TASK(Actor)->header.step++;
        TASK(Actor)->pos.y.fixed = D_801F42C8[TASK(Actor)->param.unk_0B];
        func_801A4BC0(0x29, D_801F42C8[TASK(Actor)->param.unk_0B], 0x50);
        func_801A4BC0(0x29, D_801F42C8[TASK(Actor)->param.unk_0B] + 1, 0x50);
    }
    TASK(Actor)->pos.x.fixed = -0x2B80;
    TASK(Actor)->pos.y.fixed = (TASK(Actor)->pos.y.fixed << 7) - 0x4040;
    func_801F2EFC();
    func_801F3064();
}
