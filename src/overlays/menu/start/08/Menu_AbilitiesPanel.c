#include "start_08.h"

/* func_801EA698 */
MATCH void Menu_AbilitiesPanel(void) {
    g_MenuStartAbilitiesSteps[g_UIPanelCurrent->state]();
    Menu_DrawAbilitiesPanel(g_UIPanelCurrent);
}
