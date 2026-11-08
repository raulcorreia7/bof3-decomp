#include "battle_15.h"

MATCH void func_800A4BB4(void) {
    if (EMI_IsReady() != 0) {
        GFX_CopyPalette(0x1B);
        g_GfxPalettePending = 1;
        g_BattleSubStep     = 1;
        g_BattleUIStep      = 1;
        g_BattleUIState     = 0;
    }
}
