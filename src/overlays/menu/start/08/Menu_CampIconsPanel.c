#include "start_08.h"

/* func_801E9304 */
MATCH void Menu_CampIconsPanel(void) {
    g_MenuStartCampIconsStates[g_MenuCurrentPanel->state]();
    func_801E9350();
}
