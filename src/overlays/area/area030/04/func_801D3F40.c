#include "area030_04.h"

/* Advances the area message scroll, draws its text line and icon strip. */
MATCH void func_801D3F40(void) {
    u8  id;
    u8  ch;
    u8  left;
    u8  style;
    s16 index;
    s16 scroll;

    scroll                     = (FISHING_STATE->origin_x_2E - 2);
    FISHING_STATE->origin_x_2E = scroll;
    if (scroll < 29 && FISHING_STATE->counter_49 != 0) {
        FISHING_STATE->text_54.pointer = FISHING_STATE->item_50.pointer;
        ch                             = *FISHING_STATE->item_50.pointer;
        if (ch == 0x12 || ch == 0x15) {
            FISHING_STATE->item_50.pointer = FISHING_STATE->item_50.pointer + 1;
        }
        left                           = FISHING_STATE->counter_49 - 1;
        FISHING_STATE->item_50.pointer = FISHING_STATE->item_50.pointer + 1;
        FISHING_STATE->counter_49      = left;
        FISHING_STATE->origin_x_2E     = 0x23;
        FISHING_STATE->step_timer_09   = 4;
    }
    style = FISHING_STATE->step_timer_09;
    if (style != 0) {
        style -= 1;
        FISHING_STATE->step_timer_09 = style;
        func_801D9740(0, FISHING_STATE->text_54.pointer, ((8 - ((4 - FISHING_STATE->step_timer_09) * 2)) & 0xFE) | 0x80, 0x1D);
    }
    if (FISHING_STATE->counter_49 != 0) {
        u16* ox = &D_80144154;
        UI_DrawText(FISHING_STATE->origin_x_2E, (*ox + 2), 0, FISHING_STATE->counter_49, FISHING_STATE->item_50.pointer);
        id = D_801E1E80[FISHING_STATE->row_4B * 0xC];
        if (id != GAME_NONE) {
            index = id * 3;
            UI_DrawText((FISHING_STATE->origin_x_2E + (FISHING_STATE->counter_49 * 8)), (*ox + 2), D_801E1F16[index], 1, (u8*)(index + D_801E1F14));
        }
    } else {
        id = D_801E1E80[FISHING_STATE->row_4B * 0xC];
        if (id != GAME_NONE) {
            index = id * 3;
            UI_DrawText(FISHING_STATE->origin_x_2E, (D_80144154 + 2), D_801E1F16[index], 1, (u8*)(index + D_801E1F14));
            if ((s16)FISHING_STATE->origin_x_2E == 0x1D) {
                FISHING_STATE->step_timer_09 = 4;
                FISHING_STATE->handler_index_01 += 1;
            }
        } else {
            Actor_Clear();
        }
    }
}
