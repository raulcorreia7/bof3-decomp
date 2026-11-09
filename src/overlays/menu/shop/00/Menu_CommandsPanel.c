#include "shop_00.h"

/* func_801E29C8 */
MATCH void Menu_CommandsPanel(void) {
    g_ShopCommandsStates[g_MenuCurrentPanel->state]();
    Menu_DrawCommandRow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_MenuCurrentPanel->unk_0A, g_MenuCurrentPanel->unk_0B, 0);
}
