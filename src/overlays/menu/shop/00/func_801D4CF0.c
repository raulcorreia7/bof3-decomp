#include "shop_00.h"

MATCH void func_801D4CF0(void) {
    u8* counter;
    u8  count;

    counter = &D_80148654;
    func_801DDFB0(0x62 + *counter * 0x30, 0x4C, D_801E60F8, g_SaveCardPort, 1);
    MENU_DRAW_HEADER();
    count    = *counter + 1;
    *counter = count;
    if (count == 4) {
        if (D_801E6080 != 0) {
            D_80148652 = 0x12;
        } else {
            D_80148652 = D_80148652 + 1;
        }
    }
}
