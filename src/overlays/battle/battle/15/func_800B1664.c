#include "battle_15.h"

MATCH void func_800B1664(void) {
    Battle_DrawCommandList();
    if (g_UIPanelCurrent->pos.vx >= 164) {
        g_UIPanelCurrent->pos.vx = g_UIPanelCurrent->pos.vx - 32;
    }
    if (g_UIPanelCurrent->pos.vx < 163) {
        g_UIPanelCurrent->pos.vx = 163;
    }
}
