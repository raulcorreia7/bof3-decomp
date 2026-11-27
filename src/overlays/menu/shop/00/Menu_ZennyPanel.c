#include "shop_00.h"

/* func_801E2AB0 */
MATCH void Menu_ZennyPanel(void) {
    g_ShopZennySteps[g_UIPanelCurrent->state]();
    Menu_DrawZennyWindow((u16)g_UIPanelCurrent->pos.vx, (u16)g_UIPanelCurrent->pos.vy, 0, g_Zenny);
}
