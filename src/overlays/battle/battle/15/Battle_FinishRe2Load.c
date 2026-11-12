#include "battle_15.h"

/* func_800A4BB4 */
MATCH void Battle_FinishRe2Load(void) {
    if (EMI_IsReady() != 0) {
        GFX_CopyPalette(27);
        g_GfxPalettePending     = 1;
        g_Battle.phase.sub_step = 1;
        g_Battle.ui_step        = 1;
        g_Battle.ui_state       = 0;
    }
}
