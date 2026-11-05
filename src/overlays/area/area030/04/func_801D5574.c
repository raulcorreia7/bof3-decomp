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

    FISHING_STATE->step_timer_09 += 1;
    if (FISHING_STATE->saved_index_0B == 0) {
        func_801D9534(MENU_HEADER_X, (0x12 - FISHING_STATE->step_timer_09 * 0x10) & 0xFFFE, MENU_HEADER_WIDTH,
                      MENU_HEADER_HEIGHT, 0);
        y      = 0x28;
        mask   = 0;
        t      = FISHING_STATE->step_timer_09 * 3;
        offset = t << 4;
        offset -= t;
        offset += 0x58;
        offset &= HALF_MASK;
    } else {
        func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
        mask = 0;
        if (D_80145E93[0] >= 3) {
            mask = (1 << FISHING_STATE->cue_index_06) & BYTE_MASK;
        }
        offset = 0x58;
        y      = 0x28;
    }
    func_801D7C10(offset, y, mask);
    func_801D72E4(0x27, (s16)(FISHING_STATE->step_timer_09 * 0x3C + 0x40));
    if (FISHING_STATE->step_timer_09 == 4) {
        if (FISHING_STATE->saved_index_0B == 0) {
            FISHING_STATE->handler_index_01 = 0;
        } else if (FISHING_STATE->cue_index_06 == 0) {
            FISHING_STATE->handler_index_01 = 2;
        } else if (FISHING_STATE->cue_index_06 == 1) {
            FISHING_STATE->handler_index_01 = 6;
        }
    }
}
