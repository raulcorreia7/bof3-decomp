#include "area030_04.h"

/* Advances the area panel's cursor step and draws its rows: the
 *           0x0B mode picks the full-width or indented row band, the 0x07 flag
 *           picks the normal or alternate row renderer, and at step 4 the mode
 *           sets the next cursor byte (advance or 0xC). */
MATCH void func_801D4680(void) {
    s32 x;
    s32 y;
    s32 t;
    s32 flags;

    FISHING_STATE->step_timer_09++;
    if (FISHING_STATE->saved_index_0B == 0) {
        func_801D9534(MENU_HEADER_X, (0x12 - (FISHING_STATE->step_timer_09 * 0x10)) & 0xFFFE, MENU_HEADER_WIDTH,
                      MENU_HEADER_HEIGHT, 0U);
        y     = 0x28;
        flags = 0;
        t     = FISHING_STATE->step_timer_09 * 3;
        x     = t << 4;
        x -= t;
        x += 0x58;
        x &= HALF_MASK;
    } else {
        func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0U);
        flags = 0;
        if (D_80145E93[0] >= 3) {
            flags = (1 << FISHING_STATE->cue_index_06) & BYTE_MASK;
        }
        x = 0x58;
        y = 0x28;
    }
    func_801D7C10(x, y, flags);
    func_801D88E0((0x10 - (FISHING_STATE->step_timer_09 * 0x2D)), 0x40);
    if (!(FISHING_STATE->counter_07 & 1)) {
        func_801D7EB0((s16)((FISHING_STATE->step_timer_09 * 0x2D) + 0xA4), 0x40);
    } else {
        func_801D8364(((FISHING_STATE->step_timer_09 * 0x2D) + 0xA4), 0x40);
    }
    if (FISHING_STATE->step_timer_09 == 4) {
        if (FISHING_STATE->saved_index_0B == 0) {
            FISHING_STATE->handler_index_01 = 0;
            return;
        }
        if (FISHING_STATE->cue_index_06 == 1) {
            FISHING_STATE->handler_index_01++;
        } else if (FISHING_STATE->cue_index_06 == 2) {
            FISHING_STATE->handler_index_01 = 0xC;
        }
    }
}
