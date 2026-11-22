#include "area030_04.h"

/* Advances the area message scroll, draws its text line and icon strip. */
MATCH void func_801D3F40(void) {
    u8  id;
    u8  ch;
    u8  left;
    u8  style;
    s16 index;
    s16 scroll;

    scroll                       = (TASK(FishingState)->origin_x - 2);
    TASK(FishingState)->origin_x = scroll;
    if (scroll < 29 && TASK(FishingState)->counter_49 != 0) {
        TASK(FishingState)->text.pointer = TASK(FishingState)->item.pointer;
        ch                               = *TASK(FishingState)->item.pointer;
        if (ch == 0x12 || ch == 0x15) {
            TASK(FishingState)->item.pointer = TASK(FishingState)->item.pointer + 1;
        }
        left                             = TASK(FishingState)->counter_49 - 1;
        TASK(FishingState)->item.pointer = TASK(FishingState)->item.pointer + 1;
        TASK(FishingState)->counter_49   = left;
        TASK(FishingState)->origin_x     = 0x23;
        TASK(FishingState)->step_timer   = 4;
    }
    style = TASK(FishingState)->step_timer;
    if (style != 0) {
        style -= 1;
        TASK(FishingState)->step_timer = style;
        func_801D9740(0, TASK(FishingState)->text.pointer, ((8 - ((4 - TASK(FishingState)->step_timer) * 2)) & 0xFE) | 0x80, 0x1D);
    }
    if (TASK(FishingState)->counter_49 != 0) {
        u16* ox = &D_80144154;
        UI_TextDraw(TASK(FishingState)->origin_x, (*ox + 2), 0, TASK(FishingState)->counter_49, TASK(FishingState)->item.pointer);
        id = D_801E1E80[TASK(FishingState)->row_4B * 0xC];
        if (id != GAME_NONE) {
            index = id * 3;
            UI_TextDraw((TASK(FishingState)->origin_x + (TASK(FishingState)->counter_49 * 8)), (*ox + 2), D_801E1F16[index], 1, (u8*)(index + D_801E1F14));
        }
    } else {
        id = D_801E1E80[TASK(FishingState)->row_4B * 0xC];
        if (id != GAME_NONE) {
            index = id * 3;
            UI_TextDraw(TASK(FishingState)->origin_x, (D_80144154 + 2), D_801E1F16[index], 1, (u8*)(index + D_801E1F14));
            if ((s16)TASK(FishingState)->origin_x == 0x1D) {
                TASK(FishingState)->step_timer = 4;
                TASK(FishingState)->handler_index += 1;
            }
        } else {
            Actor_Clear();
        }
    }
}
