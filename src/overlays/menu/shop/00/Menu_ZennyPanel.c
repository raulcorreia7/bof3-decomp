#include "shop_00.h"

/* func_801E2AB0 */
MATCH void Menu_ZennyPanel(void) {
    g_ShopZennySteps[g_UiPanelCurrent->state]();
    Menu_DrawZennyWindow(g_UiPanelCurrent->pos.x, g_UiPanelCurrent->pos.y, 0, g_Zenny);
}
