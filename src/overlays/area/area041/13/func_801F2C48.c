#include "area041_13.h"

MATCH void func_801F2C48(void) {
    u8 idx;

    SELF(Actor)->param.unk_0B = SELF(Actor)->pos.x.part.integer;
    idx                       = SELF(Actor)->param.unk_0B;
    if (SYS_TestFlag(g_SceneFlagRows[D_801F42CC[idx]], D_801F42D0[idx])) {
        SELF(Actor)->header.step = 3;
        SELF(Actor)->pos.y.fixed = D_801F42C8[SELF(Actor)->param.unk_0B] + 2;
    } else {
        SELF(Actor)->header.step++;
        SELF(Actor)->pos.y.fixed = D_801F42C8[SELF(Actor)->param.unk_0B];
        func_801A4BC0(0x29, D_801F42C8[SELF(Actor)->param.unk_0B], 0x50);
        func_801A4BC0(0x29, D_801F42C8[SELF(Actor)->param.unk_0B] + 1, 0x50);
    }
    SELF(Actor)->pos.x.fixed = -0x2B80;
    SELF(Actor)->pos.y.fixed = (SELF(Actor)->pos.y.fixed << 7) - 0x4040;
    func_801F2EFC();
    func_801F3064();
}
