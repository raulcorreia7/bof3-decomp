#include "battle_03.h"

MATCH void func_801EA728(void) {
    MenuPanelTask* panel = g_MenuCurrentPanel;
    s16            state = panel->pos.y;

    if (state == 0x12) {
        panel->state++;
    } else {
        panel->pos.y = state + 8;
    }
}
