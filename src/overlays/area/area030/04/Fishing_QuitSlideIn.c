#include "area030_04.h"

/* Decrements the scratchpad byte at g_Task+0x9 and passes the
 * 0x50-scaled row it selects to Fishing_DrawPromptBox with 0x56; when that byte reaches
 * zero it sets the byte at +0x6 to 1 and increments the byte at +0x3; the frame
 * then redraws through Fishing_DrawDimScreen, Fishing_DrawWindowFrame and func_8014F800 (the
 * quit prompt message). */
/* func_801DA058 */
MATCH void Fishing_QuitSlideIn(void) {
    FISHING_STATE->step_timer_09 = (FISHING_STATE->step_timer_09 - 1);
    Fishing_DrawPromptBox((s16)((FISHING_STATE->step_timer_09 * 0x50) + 0x6C), 86);
    if (FISHING_STATE->step_timer_09 == 0) {
        FISHING_STATE->cue_index_06 = 1;
        FISHING_STATE->sub_index_03 = (FISHING_STATE->sub_index_03 + 1);
    }
    Fishing_DrawDimScreen();
    Fishing_DrawWindowFrame(MENU_HEADER_X, (MENU_HEADER_Y - (FISHING_STATE->step_timer_09 * 8)) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0U);
    UI_DrawText(29, 21 - (FISHING_STATE->step_timer_09 * 8), 0, 255U, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_QUIT_PROMPT));
}
