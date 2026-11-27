#include "battle_15.h"

MATCH void func_800B0EC4(void) {
    func_800B0F9C();
    if (g_UiPanelCurrent->pos.vx >= 18) {
        g_UiPanelCurrent->pos.vx = g_UiPanelCurrent->pos.vx - 32;
    }
    if (g_UiPanelCurrent->pos.vx < 17) {
        g_UiPanelCurrent->pos.vx = 17;
    }
}
