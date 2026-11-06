#include "engine/slus/slus.h"

/* clears the two leading bytes and the state byte of the menu panel task.
 */
MATCH void func_80158E20(void) {
    g_MenuCurrentPanel->active = 0;
    g_MenuCurrentPanel->mode   = 0;
    g_MenuCurrentPanel->state  = 0;
}
