#include "battle_15.h"

MATCH void func_800B1664(void) {
    Battle_DrawCommandList();
    if ((s16)g_UiPanelCurrent->pos.x >= 164) {
        g_UiPanelCurrent->pos.x = g_UiPanelCurrent->pos.x - 32;
    }
    if ((s16)g_UiPanelCurrent->pos.x < 163) {
        g_UiPanelCurrent->pos.x = 163;
    }
}
