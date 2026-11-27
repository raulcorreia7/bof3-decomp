#include "shop_00.h"

/* func_801E2DB4 */
MATCH void Menu_EquipmentPanel(void) {
    g_ShopEquipmentSteps[g_UIPanelCurrent->state]();
    Menu_DrawEquipmentPanel(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, g_CharSlot[g_PartyFieldOrder[g_UIPanelCurrent->unk_0A]]);
}
