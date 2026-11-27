#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Draws the AREA030 prompt frame for the caret row, queues the cue the
 * pad pair selects and advances the panel step, then re-arms the panel window
 * and the prompt row. */
/* func_801DA168 */
MATCH void Fishing_QuitInput(void) {
    u16*          pad;
    FishingState* work;

    pad = &g_PadStates[0].pressed;
    Fishing_DrawPromptBox(108, 86);

    if ((*pad & (PADLup | PADLdown)) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        work            = SELF(FishingState);
        work->cue_index = (work->cue_index ^ 0x1);
    }

    if ((*pad & (PADRup | PADRdown)) != 0) {
        if ((*pad & PADRup) != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            SELF(FishingState)->cue_index = 1;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        }
        work            = SELF(FishingState);
        work->sub_index = (work->sub_index + 1);
    }

    UI_CursorDraw(112, (130 - SELF(FishingState)->cue_index * 16) & 0xFFFE, 0);
    Fishing_DrawDimScreen();
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    UI_TextDraw(29, 21, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_QUIT_PROMPT));
}
