#include "shop_00.h"

MATCH void func_801D6018(void) {
    u8 count;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    if (g_UiWindowChannel & FRONTEND_FLAG_CONFIRM) {
        if (D_8014865B == 0) {
            count      = D_80148651;
            D_80148654 = 0;
            D_80148651 = count + 1;
        } else {
            D_80148651 = 3;
            D_80148652 = 0;
        }
    }
}
