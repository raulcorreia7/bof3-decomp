#include "shop_00.h"

MATCH void func_801D46E0(void) {
    u8* counter;
    u8  count;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    counter  = &D_80148652;
    count    = *counter;
    *counter = count + 1;
}
