#include "area030_04.h"

/* Draws the AREA030 panel row, then moves the panel state when the
 * prompt page and frame state allow it: the accept cue steps the caret back,
 * right/left step the selected index with wraparound. */
MATCH void func_801DD7CC(void) {
    UI_DrawText(29, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_HOW_TO_PAGE_HINT));
    if ((D_80144281 == 0xE) && (D_80144288 == 0)) {
        if (g_InputPressed & g_InputMasks[FISHING_INPUT_CANCEL]) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            FISHING_STATE->flag_04      = 0;
            FISHING_STATE->sub_index_03 = (FISHING_STATE->sub_index_03 - 1);
            return;
        }
        if (g_InputPressed & PADLdown) {
            D_80144288 = 0xFF;
            D_801442BC = D_801442BC + 1;
            if ((D_801442BC & HALF_MASK) >= 6U) {
                D_801442BC = 0;
            }
        } else if (g_InputPressed & PADLup) {
            D_80144288 = 1;
            D_801442BC = D_801442BC - 1;
            if ((s16)D_801442BC < 0) {
                D_801442BC = 5;
            }
        }
    }
}
