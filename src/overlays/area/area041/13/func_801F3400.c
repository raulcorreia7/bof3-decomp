#include "area041_13.h"

MATCH s32 func_801F3400(void) {
    func_801F387C(D_801F4308[TASK(Actor)->timer] << 4);
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 41U) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x05));
        TASK(Actor)->timer            = 0;
        COORD_INT(TASK(Actor)->pos.z) = -0x88;
        TASK(Actor)->header.step += 1;
    }
}
