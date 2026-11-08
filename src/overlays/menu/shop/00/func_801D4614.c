#include "shop_00.h"

MATCH void func_801D4614(void) {
    u8 count;

    MENU_DRAW_HEADER();
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
