#include "shop_00.h"

MATCH void func_801D5390(void) {
    u8* cursor;
    u8  step;

    MENU_DRAW_HEADER();
    cursor = &D_80148654;
    SAVE_DrawSlots((*cursor * 0x50 + 0x20), 0x30, 0);
    step    = *cursor + 1;
    *cursor = step;
    if (step == 4) {
        if (D_801E6080 == 0) {
            g_MenuStep.state = 1;
        } else {
            g_MenuStep.state = 0x12;
        }
    }
}
