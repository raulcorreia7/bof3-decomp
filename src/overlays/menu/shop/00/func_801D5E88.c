#include "shop_00.h"

MATCH void func_801D5E88(void) {
    volatile u8* p;
    u8           val;

    switch (D_801E60EC) {
        case 23:
            Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
            WinDrawCueText(28, 22, 0x9C);
            break;
        default:
        case 20:
        case 22:
        case 24:
            Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
            WinDrawCueText(28, 22, D_801E60EC + 0x85);
            SAVE_DrawSlots(0x20, 0x30, 0);
            break;
        case 21:
        case 25:
            Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
            WinDrawCueText(28, 22, D_801E60EC + 0x85);
            func_801DDFB0(0x62, 0x4C, D_801E60F8, g_SaveCardPort, 1);
            break;
    }
    /* Pointer form: retail keeps one base register across the count load and
     * the store, which a symbol access would re-materialize. */
    p   = &D_80148654;
    val = *p - 1;
    *p  = val;
    if (val == 0) {
        D_80148652 = D_801E6094;
    }
}
