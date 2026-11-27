#include "area082_13.h"

MATCH void func_801F50C4(void) {
    D_8014933A = 0;
    Area_DrawGradient(-1);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
    SELF(Actor)->timer = 0;
    SELF(Actor)->header.step++;
}
