#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Draws the AREA030 prompt frame for the caret row, queues the cue the
 * pad pair selects and advances the panel step, then re-arms the panel window
 * and the prompt row. */
MATCH void func_801DA168(void) {
    u16*          pad;
    FishingState* work;

    pad = &g_InputPressed;
    func_801E1758(0x6C, 0x56);

    if ((*pad & (PADLup | PADLdown)) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        work               = FISHING_STATE;
        work->cue_index_06 = (u8)(work->cue_index_06 ^ 1);
    }

    if ((*pad & (PADRup | PADRdown)) != 0) {
        if ((*pad & PADRup) != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 6));
            FISHING_STATE->cue_index_06 = 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 3));
        }
        work               = FISHING_STATE;
        work->sub_index_03 = (u8)(work->sub_index_03 + 1);
    }

    Menu_DrawCursorSprite(0x70, (0x82 - FISHING_STATE->cue_index_06 * 0x10) & 0xFFFE, 0);
    func_801E16DC();
    func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    UI_DrawText(0x1D, 0x15, 0, 0xFF, (u8*)(FISHING_TEXT_BANK + D_80010080));
}
