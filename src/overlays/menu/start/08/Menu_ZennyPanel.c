#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte; draw
 * helper owned by this overlay. */

/* func_801E9140 */
MATCH void Menu_ZennyPanel(void) {
    g_MenuStartZennySteps[g_UiPanelCurrent->state]();
    Menu_DrawZennyWindow((u16)g_UiPanelCurrent->pos.vx, (u16)g_UiPanelCurrent->pos.vy, 0, g_Zenny);
}
