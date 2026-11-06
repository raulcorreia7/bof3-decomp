#include "engine/slus/slus.h"

/* when the front-end frame helper (func_801503E0) reports zero,
 * clears g_MenuPanelMode and resets the menu panel task.
 */
MATCH void func_801598B8(void) {
    if ((UI_UpdateLayout() & BYTE_MASK) == 0) {
        g_MenuPanelMode = 0;
        func_80158E20();
    }
}
