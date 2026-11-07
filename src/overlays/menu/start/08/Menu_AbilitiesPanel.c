#include "start_08.h"

/* func_801EA698 */
MATCH void Menu_AbilitiesPanel(void) {
    g_MenuStartAbilitiesStates[g_MenuCurrentPanel->state]();
    func_801E0354(g_MenuCurrentPanel);
}
