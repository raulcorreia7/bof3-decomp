#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Draws the AREA030 prompt frame for the caret row, queues the cue the
 * pad pair selects and advances the panel step, then re-arms the panel window
 * and the prompt row. */
/* func_801DA168 */
MATCH void Fishing_QuitInput(void) {
    u16*          pad;
    FishingState* work;

    pad = &g_InputPressed;
    Fishing_DrawPromptBox(108, 86);

    if ((*pad & (PADLup | PADLdown)) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        work               = FISHING_STATE;
        work->cue_index_06 = (work->cue_index_06 ^ 0x1);
    }

    if ((*pad & (PADRup | PADRdown)) != 0) {
        if ((*pad & PADRup) != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            FISHING_STATE->cue_index_06 = 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        }
        work               = FISHING_STATE;
        work->sub_index_03 = (work->sub_index_03 + 1);
    }

    Menu_DrawCursorSprite(112, (130 - FISHING_STATE->cue_index_06 * 16) & 0xFFFE, 0);
    Fishing_DrawDimScreen();
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    UI_DrawText(29, 21, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_QUIT_PROMPT));
}
