#include "area041_13.h"

MATCH s32 func_801F3400(void) {
    func_801F387C(D_801F4308[SELF(Actor)->timer] << 4);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 41U) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x05));
        SELF(Actor)->timer            = 0;
        COORD_INT(SELF(Actor)->pos.z) = -0x88;
        SELF(Actor)->header.step += 1;
    }
}
