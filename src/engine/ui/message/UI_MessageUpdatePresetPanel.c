#include "engine/slus/slus.h"

/* dispatches through a stack copy of the five-entry table using the
 * menu panel task's state byte at +3.
 */
/* func_80159A20 */
MATCH void UI_MessageUpdatePresetPanel(void) {
    struct MenuPanelSteps table;

    table = g_UiMessagePresetSteps;
    table.steps[g_UiPanelCurrent->state]();
}
