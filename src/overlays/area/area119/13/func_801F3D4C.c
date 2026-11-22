#include "area119_13.h"

MATCH void func_801F3D4C(void) {
    TASK(Actor)->timer = 0;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
    TASK(Actor)->header.step++;
}
