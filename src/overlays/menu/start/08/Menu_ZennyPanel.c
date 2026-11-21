#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte; draw
 * helper owned by this overlay. */

/* func_801E9140 */
MATCH void Menu_ZennyPanel(void) {
    g_MenuStartZennySteps[g_UiPanelCurrent->state]();
    Menu_DrawZennyWindow(g_UiPanelCurrent->pos.x, g_UiPanelCurrent->pos.y, 0, g_Zenny);
}
