#include "engine/slus/slus.h"

/* dispatches through a stack copy of the three-entry D_80149B30 table, using
 * the menu panel task's byte at +2.
 */
MATCH void func_80158F80(void) {
    struct MenuPanelModes table;

    table = D_80149B30;
    table.modes[g_MenuCurrentPanel->mode]();
}
