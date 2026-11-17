#include "engine/slus/slus.h"

/* dispatches through a stack copy of the three-entry g_MessagePanelModes table, using
 * the menu panel task's byte at +2.
 */
/* func_80158F80 */
MATCH void Menu_UpdateMessagePanel(void) {
    struct MenuPanelModes table;

    table = g_MessagePanelModes;
    table.modes[g_MenuCurrentPanel->mode]();
}
