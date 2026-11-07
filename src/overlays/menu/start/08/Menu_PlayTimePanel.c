#include "start_08.h"

/* func_801E9224 */
MATCH void Menu_PlayTimePanel(void) {
    g_MenuStartPlayTimeStates[g_MenuCurrentPanel->state]();
    Menu_DrawPlayTimeWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y);
}
