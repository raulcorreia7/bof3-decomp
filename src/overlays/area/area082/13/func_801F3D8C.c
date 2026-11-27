#include "area082_13.h"

MATCH void func_801F3D8C(void) {
    SELF(Actor)->timer++;
    if (SELF(Actor)->timer >= 17) {
        SELF(Actor)->timer = 0;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
        SELF(Actor)->header.step++;
    }
    func_801F4430();
}
