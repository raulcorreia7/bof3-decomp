#include "shop_00.h"

MATCH void func_801D46E0(void) {
    u8* counter;
    u8  count;

    MENU_DRAW_HEADER();
    counter  = &g_MenuStep.state;
    count    = *counter;
    *counter = count + 1;
}
