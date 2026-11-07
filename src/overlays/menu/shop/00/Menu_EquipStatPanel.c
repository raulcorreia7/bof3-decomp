#include "shop_00.h"

/* func_801E2C18 */
MATCH void Menu_EquipStatPanel(void) {
    g_ShopEquipStatStates[g_MenuCurrentPanel->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    Menu_DrawEquipStatWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y,
                             ((u8*)g_CharSlot)[g_PartyFieldOrder[g_MenuCurrentPanel->unk_0A]],
                             g_MenuCurrentPanel->unk_0B, g_MenuCurrentPanel->unk_0C);
}
