#include "area030_04.h"

/* Decrements the scratchpad byte at g_Task+0x9 and passes the 0x50-scaled row it selects to func_801E1758 with 0x56. */
MATCH void func_801DA058(void) {
    FISHING_STATE->step_timer_09 = (FISHING_STATE->step_timer_09 - 1);
    func_801E1758((s16)((FISHING_STATE->step_timer_09 * 0x50) + 0x6C), 0x56);
    if (FISHING_STATE->step_timer_09 == 0) {
        FISHING_STATE->cue_index_06 = 1;
        FISHING_STATE->sub_index_03 = (FISHING_STATE->sub_index_03 + 1);
    }
    func_801E16DC();
    func_801D9534(MENU_HEADER_X, (MENU_HEADER_Y - (FISHING_STATE->step_timer_09 * 8)) & 0xFFFE, MENU_HEADER_WIDTH,
                  MENU_HEADER_HEIGHT, 0U);
    UI_DrawText(29, 21 - (FISHING_STATE->step_timer_09 * 8), 0, 0xFFU,
                MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_QUIT_PROMPT));
}
