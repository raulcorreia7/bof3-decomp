#include "battle_15.h"

/* func_800B2104 */
MATCH void Battle_DrawInventoryPanel(void) {
    D_800B6E20[g_MenuCurrentPanel->state]();
    Menu_DrawInventoryWindow(g_MenuCurrentPanel);
}
