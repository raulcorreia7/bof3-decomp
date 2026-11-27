#include "battle_03.h"

/* func_801E915C */
MATCH void Battle_SlideInPartyPanel(void) {
    MenuPanelTask* panel;
    s16            value;

    panel = g_UIPanelCurrent;
    value = panel->pos.vy;
    if (value < 0xC9) {
        panel->pos.vy = 200;
        panel->state += 1;
    } else {
        panel->pos.vy = (value - 4);
    }
    Battle_DrawPartyPanel(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy);
}
