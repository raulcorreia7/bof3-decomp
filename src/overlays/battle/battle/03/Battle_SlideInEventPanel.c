#include "battle_03.h"

/* func_801EA728 */
MATCH void Battle_SlideInEventPanel(void) {
    MenuPanelTask* panel = g_UiPanelCurrent;
    s16            state = panel->pos.vy;

    if (state == 0x12) {
        panel->state++;
    } else {
        panel->pos.vy = state + 8;
    }
}
