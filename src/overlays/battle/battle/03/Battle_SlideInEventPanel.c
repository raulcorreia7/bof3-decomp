#include "battle_03.h"

/* func_801EA728 */
MATCH void Battle_SlideInEventPanel(void) {
    MenuPanelTask* panel = g_MenuCurrentPanel;
    s16            state = panel->pos.y;

    if (state == 0x12) {
        panel->state++;
    } else {
        panel->pos.y = state + 8;
    }
}
