#include "shop_00.h"

MATCH void func_801D5390(void) {
    u8* cursor;
    u8  step;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    cursor = &D_80148654;
    SAVE_DrawSlots((*cursor * 0x50 + 0x20), 0x30, 0);
    step    = *cursor + 1;
    *cursor = step;
    if (step == 4) {
        if (D_801E6080 == 0) {
            D_80148652 = 1;
        } else {
            D_80148652 = 0x12;
        }
    }
}
