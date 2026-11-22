#include "battle_15.h"

/* func_800A4744 */
MATCH void Battle_EndDraLoad(void) {
    if (EMI_IsReady() != 0) {
        GFX_PaletteCopy(26);
        GFX_PaletteCopy(27);
        g_BattleUIState = 0;
        g_GfxPalettePending++;
        /* Plain view: a volatile access pins the increment and blocks the
         * epilogue hoist the original image performs. */
        *(u8*)&g_Battle.ui_step += 1;
    }
}
