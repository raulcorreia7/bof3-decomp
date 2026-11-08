#include "start_08.h"

/* func_801EA698 */
MATCH void Menu_AbilitiesPanel(void) {
    g_MenuStartAbilitiesStates[g_MenuCurrentPanel->state]();
    Menu_DrawAbilitiesPanel(g_MenuCurrentPanel);
}
