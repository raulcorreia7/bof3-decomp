#include "area030_04.h"

/* Decrements the scratchpad byte at g_Task+0x9 and passes the
 * 0x50-scaled row it selects to func_801E1758 with 0x56; when that byte reaches
 * zero it sets the byte at +0x6 to 1 and increments the byte at +0x3; the frame
 * then redraws through func_801E16DC, func_801D9534 and func_8014F800 (the
 * D_80010080-based address). */
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
    UI_DrawText(0x1D, 0x15 - (FISHING_STATE->step_timer_09 * 8), 0, 0xFFU, (u8*)(FISHING_TEXT_BANK + D_80010080));
}
