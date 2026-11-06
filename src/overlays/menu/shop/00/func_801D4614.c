#include "shop_00.h"

MATCH void func_801D4614(void) {
    u8 count;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    if (D_8014865B == 0) {
        count      = D_80148651;
        D_80148654 = 0;
        D_80148652 = 0;
        D_80148651 = count + 2;
    } else {
        count      = D_80148651;
        D_80148654 = 0;
        D_80148652 = 0;
        D_80148651 = count + 1;
    }
}
