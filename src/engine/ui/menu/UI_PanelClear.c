#include "engine/slus/slus.h"

/* clears the two leading bytes and the state byte of the menu panel task.
 */
/* func_80158E20 */
MATCH void UI_PanelClear(void) {
    g_UIPanelCurrent->active = 0;
    g_UIPanelCurrent->mode   = 0;
    g_UIPanelCurrent->state  = 0;
}
