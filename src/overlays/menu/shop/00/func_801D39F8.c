#include "shop_00.h"
#include "area/map.h"

MATCH void func_801D39F8(void) {
    u8 count;
    u8 selection;

    /* The state byte is read before the delay counter is stored: the original
     * schedule interleaves the two accesses in that order. */
    count      = D_80148651;
    D_80148654 = 4;
    D_80148651 = count + 1;
    D_801E60F0 = 0;
    D_80148652 = 0;
    if (g_GameRequestFlags == AREA_LOAD_FLAG_SHOP || g_GameAreaId == AREA_ID_BLACK_SHIP || g_GameAreaId == AREA_ID_BOAT_AFTER_BLACK_SHIP || g_GameAreaId == AREA_ID_DESERT_ENTRANCE_CAMP) {
        selection  = D_8014865C;
        D_8014865C = -2;
        D_8014865F = selection;
    }
    if (D_8014865C == -2) {
        D_80148651 = 3;
        D_80148652 = 0;
    }
}
