#include "area030_04.h"

/* Draws the AREA030 prompt row, then steps the panel cursor from the
 * pad pair: right/left wrap the entry index and move the caret, confirm queues
 * the accept cue and steps the panel state back. */
MATCH void func_801DD664(void) {
    u8* panel;
    u16 index;

    UI_DrawText(29, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_DATA_PAGE_HINT));

    panel = &D_80144281;
    if (*panel != 8) {
        return;
    }

    if ((g_InputPressed & PADLright) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        index      = D_801442BE + 1;
        D_801442BC = index;
        if ((index & HALF_MASK) >= 0x17) {
            D_801442BC = 0;
        }
        D_80144288 = 0;
        *panel     = (*panel + 1);
        return;
    }

    if ((g_InputPressed & PADLleft) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        index      = D_801442BE - 1;
        D_801442BC = index;
        if ((s16)index < 0) {
            D_801442BC = 0x16;
        }
        D_80144288 = 1;
        *panel     = (*panel + 1);
        return;
    }

    if ((g_InputPressed & g_InputMasks[FISHING_INPUT_CANCEL]) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        FISHING_STATE->flag_04      = 0;
        FISHING_STATE->sub_index_03 = (FISHING_STATE->sub_index_03 - 1);
    }
}
