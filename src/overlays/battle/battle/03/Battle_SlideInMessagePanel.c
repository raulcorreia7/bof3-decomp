#include "battle_03.h"

/* func_801EA894 */
MATCH void Battle_SlideInMessagePanel(void) {
    MenuPanelTask* panel;
    s16            state;

    panel      = g_UiPanelCurrent;
    D_801EC2E4 = 1u;
    state      = panel->pos.vy;
    if (state == 0x12) {
        panel->state++;
    } else {
        panel->pos.vy = state + 8;
    }
    Battle_DrawMessagePanel();
}
