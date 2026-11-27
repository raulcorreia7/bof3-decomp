#include "area088_13.h"

MATCH s32 func_801F2CE4(void) {
    u8  tick;
    s32 x;

    tick               = SELF(Actor)->timer;
    SELF(Actor)->timer = tick + 1;
    if (tick == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
    }
    Trail_Update((Trail*)AREA_WORK);
    Trail_Draw(MEM_PTR(Trail, AREA_WORK));
    x                        = SELF(Actor)->pos.x.fixed + TO_COORD(1);
    SELF(Actor)->pos.x.fixed = x;
    if (x == TO_COORD(23)) {
        SELF(Actor)->timer = 32;
        SELF(Actor)->header.mode++;
    }
}
