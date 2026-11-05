#include "battle_03.h"

MATCH void func_801E915C(void) {
    MenuPanelTask* panel;
    s16            value;

    panel = g_MenuCurrentPanel;
    value = (s16)panel->y;
    if (value < 0xC9) {
        panel->y = 200;
        panel->state += 1;
    } else {
        panel->y = (u16)(value - 4);
    }
    func_801D750C((s32)(s16)g_MenuCurrentPanel->x, (s32)(s16)g_MenuCurrentPanel->y);
}
