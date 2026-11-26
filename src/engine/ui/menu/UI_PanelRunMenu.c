#include "engine/game/00/game_00.h"

/* func_801995A4 */
/* Runs the menu panel step of its state, then draws its item list. */
MATCH void UI_PanelRunMenu(void) {
    g_UiPanelSteps[g_UiPanelCurrent->state]();
    func_801999F8(g_UiPanelCurrent);
}
