#include "shop_00.h"

/* func_801E2DB4 */
MATCH void Menu_EquipmentPanel(void) {
    g_ShopEquipmentSteps[g_UiPanelCurrent->state]();
    Menu_DrawEquipmentPanel(g_UiPanelCurrent->pos.x, g_UiPanelCurrent->pos.y, g_CharSlot[g_PartyFieldOrder[g_UiPanelCurrent->unk_0A]]);
}
