#include "battle_15.h"

/* func_800A4744 */
MATCH void Battle_FinishDraLoad(void) {
    if (EMI_IsReady() != 0) {
        GFX_CopyPalette(26);
        GFX_CopyPalette(27);
        g_BattleUIState = 0;
        g_GfxPalettePending++;
        /* Plain view: a volatile access pins the increment and blocks the
         * epilogue hoist the original image performs. */
        *(u8*)&g_Battle.ui_step += 1;
    }
}
