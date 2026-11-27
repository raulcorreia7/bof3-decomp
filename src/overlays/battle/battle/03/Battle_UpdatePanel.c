#include "battle_03.h"

/* func_801E9074 */
MATCH void Battle_UpdatePanel(void) {
    BattlePanelModes handlers;

    handlers = g_BattlePanelModes;
    handlers.modes[g_UIPanelCurrent->mode]();
}
