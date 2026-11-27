#include "area030_04.h"

/* Decrements the scratchpad byte at g_Self+0x9 and passes the
 * 0x50-scaled row it selects to Fishing_DrawPromptBox with 0x56; when that byte reaches
 * zero it sets the byte at +0x6 to 1 and increments the byte at +0x3; the frame
 * then redraws through Fishing_DrawDimScreen, Fishing_DrawWindowFrame and func_8014F800 (the
 * quit prompt message). */
/* func_801DA058 */
MATCH void Fishing_QuitSlideIn(void) {
    SELF(FishingState)->timer = (SELF(FishingState)->timer - 1);
    Fishing_DrawPromptBox((s16)((SELF(FishingState)->timer * 0x50) + 0x6C), 86);
    if (SELF(FishingState)->timer == 0) {
        SELF(FishingState)->cue_index = 1;
        SELF(FishingState)->sub_index = (SELF(FishingState)->sub_index + 1);
    }
    Fishing_DrawDimScreen();
    Fishing_DrawWindowFrame(MENU_HEADER_X, (MENU_HEADER_Y - (SELF(FishingState)->timer * 8)) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0U);
    UI_TextDraw(29, 21 - (SELF(FishingState)->timer * 8), 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_QUIT_PROMPT));
}
