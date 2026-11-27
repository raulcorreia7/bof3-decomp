#include "area132_13.h"

MATCH void func_801F2E38(void) {
    func_801F385C();
    SELF(Actor)->timer = 64;
    SELF(Actor)->header.step += 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 12));
}
