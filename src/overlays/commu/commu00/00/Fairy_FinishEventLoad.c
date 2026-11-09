#include "commu00_00.h"

/* Cleared here: D_801F2944/D_801F2945 also serve func_801F23A4's selection
 * latch, while the four bytes D_801F294C..D_801F294F have no reader. */

/* func_801F17A4 */
MATCH void Fairy_FinishEventLoad(void) {
    if (EMI_IsReady()) {
        GFX_ResetPalette();
        g_GfxPalettePending = 1;
        D_801F294C          = 0;
        D_801F294D          = 0;
        D_801F294E          = 0;
        D_801F294F          = 0;
        D_801F2944          = 0;
        D_801F2945          = 0;
        FAIRY_EVENT_STEP    = FAIRY_EVENT_STEP + 1;
    }
}
