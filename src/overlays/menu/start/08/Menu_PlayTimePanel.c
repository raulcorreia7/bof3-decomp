#include "start_08.h"

/* func_801E9224 */
MATCH void Menu_PlayTimePanel(void) {
    g_MenuStartPlayTimeSteps[g_UiPanelCurrent->state]();
    Menu_DrawPlayTimeWindow(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy);
}
