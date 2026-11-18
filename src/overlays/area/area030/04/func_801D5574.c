#include "area030_04.h"

/* Advances the scratchpad step byte, draws the AREA030 frame (its
 * width shrinks by 0x10 per step when the direction byte is clear, otherwise
 * fixed) and the strip at the step-derived offset, then on step 4 sets the next
 * work step from the direction byte: 0 with no direction, else 2 for 0 and 6
 * for 1. */
MATCH void func_801D5574(void) {
    s32 offset;
    s32 y;
    s32 mask;
    s32 t;

    FISHING_STATE->step_timer += 1;
    if (FISHING_STATE->saved_index == 0) {
        Fishing_DrawWindowFrame(MENU_HEADER_X, (MENU_HEADER_Y - FISHING_STATE->step_timer * 16) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
        y      = FISHING_SHOP_COLUMNS_Y;
        mask   = 0;
        t      = FISHING_STATE->step_timer * 3;
        offset = t << 4;
        offset -= t;
        offset += FISHING_SHOP_COLUMNS_X;
        offset &= HALF_MASK;
    } else {
        Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
        mask = 0;
        if (D_80145E93[0] >= 3) {
            mask = (1 << FISHING_STATE->cue_index) & BYTE_MASK;
        }
        offset = FISHING_SHOP_COLUMNS_X;
        y      = FISHING_SHOP_COLUMNS_Y;
    }
    func_801D7C10(offset, y, mask);
    func_801D72E4(39, (FISHING_STATE->step_timer * 60 + 64));
    if (FISHING_STATE->step_timer == 4) {
        if (FISHING_STATE->saved_index == 0) {
            FISHING_STATE->handler_index = 0;
        } else if (FISHING_STATE->cue_index == 0) {
            FISHING_STATE->handler_index = 2;
        } else if (FISHING_STATE->cue_index == 1) {
            FISHING_STATE->handler_index = 6;
        }
    }
}
