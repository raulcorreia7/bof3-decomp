#include "start_08.h"

/* func_801E9304 */
MATCH void Menu_CampIconsPanel(void) {
    g_MenuStartCampIconsSteps[g_UiPanelCurrent->state]();
    Menu_DrawCampIcons();
}
