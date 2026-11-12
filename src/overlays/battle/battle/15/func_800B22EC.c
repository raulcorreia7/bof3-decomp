#include "battle_15.h"

MATCH void func_800B22EC(void) {
    MenuPanelTask* panel;

    panel = g_MenuCurrentPanel;
    panel->pos.x -= 32;
    if ((s16)panel->pos.x < 83) {
        panel->pos.x = 83;
        panel->state = 0;
    }
}
