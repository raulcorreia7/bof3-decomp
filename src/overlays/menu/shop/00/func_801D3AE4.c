#include "shop_00.h"

MATCH void func_801D3AE4(void) {
    u8* counter;
    u8  cursor;
    u8  count;
    u8  next;

    counter = &D_80148654;
    cursor  = *counter;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x12 - cursor * 20) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    count = *counter;
    count--;
    *counter = count;
    if (count == 0) {
        next       = D_80148652;
        D_8014865B = 1;
        D_80148652 = next + 1;
        if (D_8014865C != -1) {
            Message_Request(0xD1);
        }
    }
}
