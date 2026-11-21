#include "battle_15.h"

MATCH void func_800B16D0(void) {
    s16 value;

    Battle_DrawCommandList();
    value = g_UiPanelCurrent->pos.x;
    if (value >= 0x143) {
        UI_PanelClear();
    } else {
        g_UiPanelCurrent->pos.x = (value + 32);
    }
}
