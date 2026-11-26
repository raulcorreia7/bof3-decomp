#include "area030_04.h"

/* Advances the area message scroll, draws its text line and icon strip. */
MATCH void func_801D3F40(void) {
    u8  id;
    u8  ch;
    u8  left;
    u8  style;
    s16 index;
    s16 scroll;

    scroll                       = (SELF(FishingState)->origin_x - 2);
    SELF(FishingState)->origin_x = scroll;
    if (scroll < 29 && SELF(FishingState)->counter_49 != 0) {
        SELF(FishingState)->text.pointer = SELF(FishingState)->item.pointer;
        ch                               = *SELF(FishingState)->item.pointer;
        if (ch == 0x12 || ch == 0x15) {
            SELF(FishingState)->item.pointer = SELF(FishingState)->item.pointer + 1;
        }
        left                             = SELF(FishingState)->counter_49 - 1;
        SELF(FishingState)->item.pointer = SELF(FishingState)->item.pointer + 1;
        SELF(FishingState)->counter_49   = left;
        SELF(FishingState)->origin_x     = 0x23;
        SELF(FishingState)->timer        = 4;
    }
    style = SELF(FishingState)->timer;
    if (style != 0) {
        style -= 1;
        SELF(FishingState)->timer = style;
        func_801D9740(0, SELF(FishingState)->text.pointer, ((8 - ((4 - SELF(FishingState)->timer) * 2)) & 0xFE) | 0x80, 0x1D);
    }
    if (SELF(FishingState)->counter_49 != 0) {
        u16* ox = &D_80144154;
        UI_TextDraw(SELF(FishingState)->origin_x, (*ox + 2), 0, SELF(FishingState)->counter_49, SELF(FishingState)->item.pointer);
        id = D_801E1E80[SELF(FishingState)->row_4B * 0xC];
        if (id != GAME_NONE) {
            index = id * 3;
            UI_TextDraw((SELF(FishingState)->origin_x + (SELF(FishingState)->counter_49 * 8)), (*ox + 2), D_801E1F16[index], 1, (u8*)(index + D_801E1F14));
        }
    } else {
        id = D_801E1E80[SELF(FishingState)->row_4B * 0xC];
        if (id != GAME_NONE) {
            index = id * 3;
            UI_TextDraw(SELF(FishingState)->origin_x, (D_80144154 + 2), D_801E1F16[index], 1, (u8*)(index + D_801E1F14));
            if ((s16)SELF(FishingState)->origin_x == 0x1D) {
                SELF(FishingState)->timer = 4;
                SELF(FishingState)->handler_index += 1;
            }
        } else {
            Actor_Clear();
        }
    }
}
