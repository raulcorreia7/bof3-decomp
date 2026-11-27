#include "start_08.h"

/* func_801E9224 */
MATCH void Menu_PlayTimePanel(void) {
    g_MenuStartPlayTimeSteps[g_UIPanelCurrent->state]();
    Menu_DrawPlayTimeWindow(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy);
}
