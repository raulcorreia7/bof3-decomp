#include "battle_15.h"

MATCH void func_800B1664(void) {
    Battle_DrawCommandList();
    if (g_UiPanelCurrent->pos.vx >= 164) {
        g_UiPanelCurrent->pos.vx = g_UiPanelCurrent->pos.vx - 32;
    }
    if (g_UiPanelCurrent->pos.vx < 163) {
        g_UiPanelCurrent->pos.vx = 163;
    }
}
