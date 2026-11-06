#include "shop_00.h"

/* File-local declarations: shared fill-style byte, shop panel/state bytes, the
 * panel mode/flag bytes and helpers owned by this target or the executable
 * overlay. */

MATCH void func_801D5D98(void) {
    u8  count;
    u8* panel_state;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_SaveData.window_style);
    panel_state  = &D_80148652;
    *panel_state = 0;
    if (D_801E60F0 == 2 || D_8014865C == -2) {
        if (D_80143BB4 != 0 && D_801E6110 == 0) {
            g_InputRepeatButtons = 0;
            g_InputRepeatDelay   = 0;
            D_8014865B           = 0;
            *panel_state         = 0x14;
            Resource_RequestArea(0xD0);
        } else {
            count      = D_80148651;
            D_80148654 = 0;
            D_80148651 = count + 1;
        }
    } else {
        D_80148651   = 1;
        *panel_state = 1;
    }
}
