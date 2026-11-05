#include "battle_03.h"

MATCH void func_801EA894(void) {
    MenuPanelTask* panel;
    s16            state;

    panel      = g_MenuCurrentPanel;
    D_801EC2E4 = 1u;
    state      = panel->y;
    if (state == 0x12) {
        panel->state++;
    } else {
        panel->y = state + 8;
    }
    func_801EAAB8();
}
