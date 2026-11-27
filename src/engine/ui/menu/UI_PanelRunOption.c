#include "engine/game/00/game_00.h"

/* func_801996A8 */
/* Runs the option panel step of its state, then draws it. */
MATCH void UI_PanelRunOption(void) {
    g_MenuOptionSteps[g_UIPanelCurrent->state]();
    func_801D7AD0(g_UIPanelCurrent);
}
