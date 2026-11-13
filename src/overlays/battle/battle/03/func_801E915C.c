#include "battle_03.h"

MATCH void func_801E915C(void) {
    MenuPanelTask* panel;
    s16            value;

    panel = g_MenuCurrentPanel;
    value = panel->pos.y;
    if (value < 0xC9) {
        panel->pos.y = 200;
        panel->state += 1;
    } else {
        panel->pos.y = (value - 4);
    }
    Battle_SetPartyCount((s16)g_MenuCurrentPanel->pos.x, (s16)g_MenuCurrentPanel->pos.y);
}
