#include "shop_00.h"

MATCH void func_801D60B0(void) {
    u8* counter;
    u8  cursor;
    u8  count;

    counter = &D_80148654;
    cursor  = *counter;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x12 - cursor * 20) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, D_80144952);
    count = *counter;
    count++;
    *counter = count;
    if (count == 5) {
        D_80148650 = 1;
        D_80148651 = 0;
        if (g_GameRequestFlags == 0x40 || g_GameAreaId == 188 || g_GameAreaId == 133 || g_GameAreaId == 193) {
            D_8014865C = D_8014865F;
        }
    }
}
