#include "engine/slus/slus.h"

/* dispatches through a stack copy of the three-entry g_UIMessagePanelModes table, using
 * the menu panel task's byte at +2.
 */
/* func_80158F80 */
MATCH void UI_MessageUpdatePanel(void) {
    struct MenuPanelModes table;

    table = g_UIMessagePanelModes;
    table.modes[g_UIPanelCurrent->mode]();
}
