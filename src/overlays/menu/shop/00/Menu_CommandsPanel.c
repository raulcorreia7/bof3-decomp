#include "shop_00.h"

/* func_801E29C8 */
MATCH void Menu_CommandsPanel(void) {
    g_ShopCommandsSteps[g_UIPanelCurrent->state]();
    Menu_DrawCommandRow(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, g_UIPanelCurrent->unk_0A, g_UIPanelCurrent->unk_0B, 0);
}
