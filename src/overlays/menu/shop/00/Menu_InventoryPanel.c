#include "shop_00.h"

/* func_801E3720 */
MATCH void Menu_InventoryPanel(void) {
    g_ShopInventorySteps[g_UiPanelCurrent->state]();
    Menu_DrawInventoryWindow(g_UiPanelCurrent);
}
