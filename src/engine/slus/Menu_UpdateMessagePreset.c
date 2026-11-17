#include "engine/slus/slus.h"

/* dispatches through a stack copy of the five-entry table using the
 * menu panel task's state byte at +3.
 */
/* func_80159A20 */
MATCH void Menu_UpdateMessagePreset(void) {
    struct MenuPanelSteps table;

    table = g_MessagePresetSteps;
    table.steps[g_MenuCurrentPanel->state]();
}
