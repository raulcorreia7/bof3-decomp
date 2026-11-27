#include "battle_15.h"

MATCH void func_800B22EC(void) {
    MenuPanelTask* panel;

    panel = g_UIPanelCurrent;
    panel->pos.vx -= 32;
    if (panel->pos.vx < 83) {
        panel->pos.vx = 83;
        panel->state  = 0;
    }
}
