#include "shop_00.h"

/* func_801E3720 */
MATCH void Menu_InventoryPanel(void) {
    g_ShopInventorySteps[g_UIPanelCurrent->state]();
    Menu_DrawInventoryWindow(g_UIPanelCurrent);
}
