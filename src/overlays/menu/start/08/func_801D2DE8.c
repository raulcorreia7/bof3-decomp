#include "start_08.h"

MATCH void func_801D2DE8(void) {
    Menu_DrawClutStrip(D_80144953);
    func_801D4884();
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    D_801ED618 = 0;
    D_80148654 = 5;
    D_80148651 += 1;
}
