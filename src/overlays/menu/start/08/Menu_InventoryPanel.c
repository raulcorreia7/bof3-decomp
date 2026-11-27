#include "start_08.h"

/* func_801E9F5C */
MATCH void Menu_InventoryPanel(void) {
    g_MenuStartInventorySteps[g_UIPanelCurrent->state]();
    Menu_DrawInventoryWindow(g_UIPanelCurrent);
}
