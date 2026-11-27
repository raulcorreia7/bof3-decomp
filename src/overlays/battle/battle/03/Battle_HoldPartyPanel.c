#include "battle_03.h"

/* func_801E91CC */
MATCH void Battle_HoldPartyPanel(void) {
    MenuPanelTask* panel = g_UIPanelCurrent;

    Battle_DrawPartyPanel(panel->pos.vx, panel->pos.vy);
}
