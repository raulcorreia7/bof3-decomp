#include "engine/slus/slus.h"

/* dispatches through a stack copy of the five-entry table using the
 * menu panel task's state byte at +3.
 */
/* func_801598F4 */
MATCH void UI_MessageUpdateChoicePanel(void) {
    struct MenuPanelSteps table;

    table = g_UiMessageChoiceSteps;
    table.steps[g_UiPanelCurrent->state]();
}
