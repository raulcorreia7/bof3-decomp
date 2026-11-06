#include "battle_03.h"

MATCH void func_801E915C(void) {
    MenuPanelTask* panel;
    s16            value;

    panel = g_MenuCurrentPanel;
    value = panel->y;
    if (value < 0xC9) {
        panel->y = 200;
        panel->state += 1;
    } else {
        panel->y = (value - 4);
    }
    func_801D750C((s16)g_MenuCurrentPanel->x, (s16)g_MenuCurrentPanel->y);
}
