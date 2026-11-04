#include "area077_14.h"

MATCH void func_801F36E8(s32 x, s32 y) {
    RECT rect;

    rect.x = x + 4;
    rect.y = y + 4;
    rect.w = 0x40;
    rect.h = 0x40;
    func_801F3198(1);
    if (D_800E4800 >= rect.x && D_800E4800 < rect.x + rect.w) {
        func_801F3B48((void*)AREA_WORK_WINDOW_ADDRESS, 0x80);
    }
    func_801F3778(0x48, (void*)AREA_WORK_WINDOW_ADDRESS, &rect);
}
