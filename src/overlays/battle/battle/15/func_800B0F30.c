#include "battle_15.h"

MATCH void func_800B0F30(void) {
    func_800B0F9C();
    if (g_UIPanelCurrent->pos.vx < 91) {
        g_UIPanelCurrent->pos.vx = g_UIPanelCurrent->pos.vx + 32;
    }
    if (g_UIPanelCurrent->pos.vx >= 92) {
        g_UIPanelCurrent->pos.vx = 91;
    }
}
