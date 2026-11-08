#include "battle_15.h"

MATCH void func_800A4744(void) {
    if (EMI_IsReady() != 0) {
        GFX_CopyPalette(0x1A);
        GFX_CopyPalette(0x1B);
        g_BattleUIState = 0;
        g_GfxPalettePending++;
        /* Plain view: a volatile access pins the increment and blocks the
         * epilogue hoist the original image performs. */
        *(u8*)&g_BattleUIStep += 1;
    }
}
