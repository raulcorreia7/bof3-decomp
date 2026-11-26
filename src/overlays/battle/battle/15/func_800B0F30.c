#include "battle_15.h"

MATCH void func_800B0F30(void) {
    func_800B0F9C();
    if (g_UiPanelCurrent->pos.vx < 91) {
        g_UiPanelCurrent->pos.vx = g_UiPanelCurrent->pos.vx + 32;
    }
    if (g_UiPanelCurrent->pos.vx >= 92) {
        g_UiPanelCurrent->pos.vx = 91;
    }
}
