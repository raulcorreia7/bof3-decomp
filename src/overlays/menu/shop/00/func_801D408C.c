#include "shop_00.h"

MATCH void func_801D408C(void) {
    u8* counter;
    u8* state;
    s8  count;
    s16 incr;

    counter = &D_80148654;
    func_801D6D6C(*counter * 48 + 0x6E, 0x4C);
    MENU_DRAW_HEADER();
    if (D_8014865C != -1) {
        Menu_DrawZennyWindow(MENU_ZENNY_WINDOW_X, MENU_ZENNY_WINDOW_Y, 0, g_Zenny);
    }
    count    = *counter;
    count    = count + 1;
    *counter = count;
    if ((count & BYTE_MASK) == 6) {
        if (D_801E60F4 != 0) {
            count      = D_80148651;
            *counter   = 0;
            D_80148651 = count + 3;
        } else {
            if (D_801E60F0 == 0) {
                *counter = 0x2D;
            } else {
                *counter = 0;
            }
            state      = &D_80148651;
            D_80148652 = 0;
            incr       = *state + 1;
            *state     = D_801E60F0 + incr;
        }
    }
}
