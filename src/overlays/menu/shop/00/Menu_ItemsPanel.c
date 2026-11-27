#include "shop_00.h"

/* func_801E2EB0 */
MATCH void Menu_ItemsPanel(void) {
    g_ShopItemsSteps[g_UIPanelCurrent->state]();
    Shop_DrawItems((MenuListPanel*)g_UIPanelCurrent);
}
