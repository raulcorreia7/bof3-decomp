#include "engine/slus/slus.h"

/* dispatches through a stack copy of the five-entry table using the
 * menu panel task's state byte at +3.
 */
MATCH void func_80158FE0(void) {
    struct MenuPanelSteps table;

    table = D_80149B3C;
    table.steps[g_MenuCurrentPanel->state]();
}
