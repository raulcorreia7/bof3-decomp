#include "shop_00.h"

/* File-local declarations: the panel handler table selected by panel-task
 * byte 3 and the shop draw helper are owned by this overlay. */

/* func_801E3E4C */
MATCH void Menu_CharacterPanel(void) {
    g_ShopCharacterSteps[g_UIPanelCurrent->state]();
    Menu_DrawCharacterWindow((u16)g_UIPanelCurrent->pos.vx, (u16)g_UIPanelCurrent->pos.vy, g_UIPanelCurrent->unk_0A, 0, 0);
}
