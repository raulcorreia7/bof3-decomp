#include "start_08.h"

/* func_801E9F5C */
MATCH void Menu_InventoryPanel(void) {
    g_MenuStartInventoryStates[g_MenuCurrentPanel->state]();
    Menu_DrawInventoryWindow(g_MenuCurrentPanel);
}
