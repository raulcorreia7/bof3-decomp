#include "shop_00.h"

/* func_801E2AB0 */
MATCH void Menu_ZennyPanel(void) {
    g_ShopZennySteps[g_UiPanelCurrent->state]();
    Menu_DrawZennyWindow((u16)g_UiPanelCurrent->pos.vx, (u16)g_UiPanelCurrent->pos.vy, 0, g_Zenny);
}
