#include "shop_00.h"

/* func_801E29C8 */
MATCH void Menu_CommandsPanel(void) {
    g_ShopCommandsSteps[g_UiPanelCurrent->state]();
    Menu_DrawCommandRow(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy, g_UiPanelCurrent->unk_0A, g_UiPanelCurrent->unk_0B, 0);
}
