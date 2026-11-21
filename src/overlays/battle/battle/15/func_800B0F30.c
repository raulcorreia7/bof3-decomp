#include "battle_15.h"

MATCH void func_800B0F30(void) {
    func_800B0F9C();
    if ((s16)g_UiPanelCurrent->pos.x < 91) {
        g_UiPanelCurrent->pos.x = g_UiPanelCurrent->pos.x + 32;
    }
    if ((s16)g_UiPanelCurrent->pos.x >= 92) {
        g_UiPanelCurrent->pos.x = 91;
    }
}
