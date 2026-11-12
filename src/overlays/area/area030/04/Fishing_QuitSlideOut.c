#include "area030_04.h"

/* Advances the menu row counter, passes the row's 0x50-scaled window
 * position to the row redraw, and on the last row resets the counter and bumps
 * the state counter selected by the record flag; the frame then redraws the
 * panel and the address-based cursor. */
/* func_801DA2A0 */
MATCH void Fishing_QuitSlideOut(void) {
    u8*  work;
    u8*  byte_counter;
    u16* word_counter;

    FISHING_STATE->step_timer_09 = (FISHING_STATE->step_timer_09 + 1);
    Fishing_DrawPromptBox((s16)(0x6C - (FISHING_STATE->step_timer_09 * 0x50)), 86);
    work = (u8*)g_Task;
    if (work[9] == 5) {
        work[9] = 0;
        work    = (u8*)g_Task;
        if (work[6] == 0) {
            word_counter = &g_GameEntrySubstate;
            *word_counter += 1;
        } else {
            byte_counter = &D_8014403D;
            *byte_counter += 1;
            work[3] = 0;
        }
    }
    Fishing_DrawDimScreen();
    if (FISHING_STATE->step_timer_09 != 0) {
        Fishing_DrawWindowFrame(MENU_HEADER_X, (MENU_HEADER_Y - (FISHING_STATE->step_timer_09 * 8)) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
        UI_DrawText(29, 21 - (FISHING_STATE->step_timer_09 * 8), 0, 255U, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_QUIT_PROMPT));
    }
}
