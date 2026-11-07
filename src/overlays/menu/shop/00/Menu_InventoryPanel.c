#include "shop_00.h"

/* func_801E3720 */
MATCH void Menu_InventoryPanel(void) {
    g_ShopInventoryStates[g_MenuCurrentPanel->state]();
    Menu_DrawInventoryWindow(g_MenuCurrentPanel);
}
