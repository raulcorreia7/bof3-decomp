#include "shop_00.h"

/* File-local declarations: shared fill-style byte, shop selection byte, the
 * 4-entry result table and helpers owned by this target or the executable
 * overlay. */

MATCH void func_801D41EC(void) {
    s16 i;
    s16 index;
    s16 value;
    u8  count;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_SaveData.window_style);
    if (D_8014865C != -1) {
        WinDrawCueText(28, 22, 0xA4);
    }
    count      = D_80148654 - 1;
    D_80148654 = count;
    if ((count & BYTE_MASK) == 0) {
        D_80148652 += 1;
        UI_SetMode(0);
        for (i = 0; i < 4; i++) {
            index             = i;
            value             = SsIsEos(0, index);
            D_801E6100[index] = value;
            if (value != 0) {
                SsSepPause(0, index);
            }
        }
    }
}
