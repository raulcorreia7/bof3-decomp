#include "shop_00.h"
#include "area/map.h"

MATCH void func_801D60B0(void) {
    u8* counter;
    u8  cursor;
    u8  count;

    counter = &D_80148654;
    cursor  = *counter;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x12 - cursor * 20) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    count = *counter;
    count++;
    *counter = count;
    if (count == 5) {
        g_MenuStep.step     = 1;
        g_MenuStep.sub_step = 0;
        if (g_GameRequestFlags == AREA_LOAD_FLAG_SHOP || g_GameAreaId == AREA_ID_BLACK_SHIP || g_GameAreaId == AREA_ID_BOAT_AFTER_BLACK_SHIP || g_GameAreaId == AREA_ID_DESERT_ENTRANCE_CAMP) {
            D_8014865C = D_8014865F;
        }
    }
}
