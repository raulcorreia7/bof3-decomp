#include "battle_03.h"

/* func_801E91CC */
MATCH void Battle_HoldPartyPanel(void) {
    MenuPanelTask* panel = g_UiPanelCurrent;

    Battle_DrawPartyPanel((s16)panel->pos.x, (s16)panel->pos.y);
}
