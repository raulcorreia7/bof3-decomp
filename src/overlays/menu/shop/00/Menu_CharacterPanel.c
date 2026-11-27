#include "shop_00.h"

/* File-local declarations: the panel handler table selected by panel-task
 * byte 3 and the shop draw helper are owned by this overlay. */

/* func_801E3E4C */
MATCH void Menu_CharacterPanel(void) {
    g_ShopCharacterSteps[g_UiPanelCurrent->state]();
    Menu_DrawCharacterWindow((u16)g_UiPanelCurrent->pos.vx, (u16)g_UiPanelCurrent->pos.vy, g_UiPanelCurrent->unk_0A, 0, 0);
}
