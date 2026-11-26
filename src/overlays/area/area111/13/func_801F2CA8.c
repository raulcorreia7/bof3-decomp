#include "area111_13.h"

MATCH void func_801F2CA8(void) {
    Actor* work = SELF(Actor);

    work->timer    = 40;
    work->screen_x = 0;
    work->screen_y = 256;
    SELF(Actor)->header.mode++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x06));
}
