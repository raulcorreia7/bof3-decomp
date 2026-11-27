#include "area105_13.h"

MATCH void func_801F2CDC(void) {
    if (g_AreaSceneMode == 2) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
        FIELD(u8, g_Self, 0x2u)++;
    }
    func_801F2D9C(0);
}
