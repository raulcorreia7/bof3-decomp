#include "shop_00.h"

MATCH void func_801D5E88(void) {
    volatile u8* p;
    u8           val;

    switch (D_801E60EC) {
        case SAVE_WAIT_PROBE:
            MENU_DRAW_HEADER();
            WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0x9C);
            break;
        default:
        case SAVE_WAIT_OVERWRITE:
        case SAVE_WAIT_CREATE:
        case 24:
            MENU_DRAW_HEADER();
            WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, D_801E60EC + 0x85);
            SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 0);
            break;
        case SAVE_WAIT_FORMAT:
        case SAVE_WAIT_SCAN:
            MENU_DRAW_HEADER();
            WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, D_801E60EC + 0x85);
            SAVE_DrawPortTabs(98, 76, D_801E60F8, g_SaveCardPort, 1);
            break;
    }
    /* Pointer form: retail keeps one base register across the count load and
     * the store, which a symbol access would re-materialize. */
    p   = &D_80148654;
    val = *p - 1;
    *p  = val;
    if (val == 0) {
        g_MenuStep.state = D_801E6094;
    }
}
