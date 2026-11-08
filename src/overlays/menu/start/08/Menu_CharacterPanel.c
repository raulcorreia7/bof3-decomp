#include "start_08.h"

/* func_801E8D60 */
MATCH void Menu_CharacterPanel(void) {
    g_MenuStartCharacterStates[g_MenuCurrentPanel->state]();
    Menu_DrawCharacterPanel(g_MenuCurrentPanel);
}
