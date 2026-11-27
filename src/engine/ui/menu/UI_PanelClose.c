#include "engine/slus/slus.h"

/* when the front-end frame helper (func_801503E0) reports zero,
 * clears g_UIPanelMode and resets the menu panel task.
 */
MATCH void UI_PanelClose(void) {
    if ((UI_MessageUpdateLayout() & BYTE_MASK) == 0) {
        g_UIPanelMode = 0;
        UI_PanelClear();
    }
}
