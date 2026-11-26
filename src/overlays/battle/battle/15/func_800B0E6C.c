#include "battle_15.h"

MATCH void func_800B0E6C(void) {
    s16 value;

    func_800B0F9C();
    value = g_UiPanelCurrent->pos.vx;
    if (value < -0xA4) {
        UI_PanelClear();
    } else {
        g_UiPanelCurrent->pos.vx = (value - 32);
    }
}
