#include "battle_15.h"

MATCH void func_800B22EC(void) {
    MenuPanelTask* panel;

    panel = g_MenuCurrentPanel;
    panel->pos.x -= 0x20;
    if ((s16)panel->pos.x < 0x53) {
        panel->pos.x = 83;
        panel->state = 0;
    }
}
