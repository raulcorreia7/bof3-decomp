#include "engine/slus/slus.h"

/* when the front-end frame helper (func_801503E0) reports zero,
 * clears g_MenuPanelMode and resets the menu panel task.
 */
MATCH void Menu_ClosePanel(void) {
    if ((UI_UpdateLayout() & BYTE_MASK) == 0) {
        g_MenuPanelMode = 0;
        Menu_ClearPanel();
    }
}
