#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte; draw
 * helper owned by this overlay. */

/* func_801E9140 */
MATCH void Menu_ZennyPanel(void) {
    g_MenuStartZennyStates[g_MenuCurrentPanel->state]();
    Menu_DrawZennyWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0, g_Zenny);
}
