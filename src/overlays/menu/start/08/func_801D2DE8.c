#include "start_08.h"

MATCH void func_801D2DE8(void) {
    Menu_DrawClutStrip(g_WindowClut);
    func_801D4884();
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
    D_801ED618 = 0;
    D_80148654 = 5;
    D_80148651 += 1;
}
