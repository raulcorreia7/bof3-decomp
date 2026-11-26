#include "area098_13.h"

MATCH void func_801F36A0(void) {
    Actor* work;

    if (SELF(Actor)->timer == 20) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x05));
    }
    if (SELF(Actor)->timer < 21U) {
        SELF(Actor)->timer += 1;
    }
    func_801F4490(&SELF(Actor)->pos, SELF(Actor)->vx, SELF(Actor)->vy);
    work = SELF(Actor);
    work->unk_18 += 128;
    work->unk_1C += 140;
    work->vx -= work->unk_18;
    work->vy -= work->unk_1C;
    if (work->vx < 0) {
        work->vx = 0;
    }
    if (SELF(Actor)->vy < 0) {
        SELF(Actor)->vy = 0;
    }
    if (func_801F42E8() == 0) {
        if ((SELF(Actor)->vx == 0) && (SELF(Actor)->vy == 0)) {
            Actor_Clear();
        }
    }
}
