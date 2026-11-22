#include "area173_14.h"

MATCH void func_801F3570(void) {
    s16* slot;

    slot       = &D_1F800038;
    *slot      = -0x40;
    D_1F80003A = 0;
    func_801F3954(0);
    *slot = 64;
    func_801F3954(1);
    *slot = 0;
    func_801F3954(2);
    TASK(Actor)->timer++;
    if (TASK(Actor)->timer >= 31) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
        TASK(Actor)->timer = 8;
        TASK(Actor)->header.step++;
    }
}
