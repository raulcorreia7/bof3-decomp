#include "battle_15.h"

MATCH void func_800B0A54(void) {
    s16 value;

    value                    = g_UiPanelCurrent->pos.vy;
    g_UiPanelCurrent->pos.vy = (value < 0x29 ? value + 16 : 41);
    func_800B0B0C(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy);
}
