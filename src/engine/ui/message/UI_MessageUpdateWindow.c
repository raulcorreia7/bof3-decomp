#include "engine/slus/slus.h"

/* dispatches through a stack copy of the five-entry table using the
 * menu panel task's state byte at +3.
 */
/* func_80158FE0 */
MATCH void UI_MessageUpdateWindow(void) {
    struct MenuPanelSteps table;

    table = g_UIMessageWindowSteps;
    table.steps[g_UIPanelCurrent->state]();
}
