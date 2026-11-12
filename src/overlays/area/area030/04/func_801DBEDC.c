#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callees. */

/* Draws the AREA030 prompt rows for the current slot, arms the cursor
 * and caption rows, and retires the panel when the confirm bits arrive. */
MATCH void func_801DBEDC(void) {
    s32 offset;

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 66);

    if ((g_InputPressed & (PADRup | PADRdown)) != 0) {
        FISHING_STATE->sub_index_03 = 0xE;
    }
    Actor_StepAnimLoop();
    Fishing_DrawDimScreen();
}
