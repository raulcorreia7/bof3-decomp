#include "battle_15.h"

MATCH void func_800B22EC(void) {
    MenuPanelTask* panel;

    panel = g_MenuCurrentPanel;
    panel->x -= 0x20;
    if ((s16)panel->x < 0x53) {
        panel->x     = 83;
        panel->state = 0;
    }
}
