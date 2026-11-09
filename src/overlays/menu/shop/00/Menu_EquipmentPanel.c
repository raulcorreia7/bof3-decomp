#include "shop_00.h"

/* func_801E2DB4 */
MATCH void Menu_EquipmentPanel(void) {
    g_ShopEquipmentStates[g_MenuCurrentPanel->state]();
    Shop_DrawEquipment(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_CharSlot[g_PartyFieldOrder[g_MenuCurrentPanel->unk_0A]]);
}
