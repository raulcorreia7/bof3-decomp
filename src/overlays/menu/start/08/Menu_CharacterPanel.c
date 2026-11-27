#include "start_08.h"

/* func_801E8D60 */
MATCH void Menu_CharacterPanel(void) {
    g_MenuStartCharacterSteps[g_UIPanelCurrent->state]();
    Menu_DrawCharacterPanel(g_UIPanelCurrent);
}
