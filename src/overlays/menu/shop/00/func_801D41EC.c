#include "shop_00.h"

/* File-local declarations: shared fill-style byte, shop selection byte, the
 * 4-entry result table and helpers owned by this target or the executable
 * overlay. */

MATCH void func_801D41EC(void) {
    s16 i;
    s16 index;
    s16 value;
    u8  count;

    MENU_DRAW_HEADER();
    if (D_8014865C != -1) {
        WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0xA4);
    }
    count      = D_80148654 - 1;
    D_80148654 = count;
    if ((count & BYTE_MASK) == 0) {
        D_80148652 += 1;
        UI_SetMode(UI_MODE_FADE_OUT);
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
