#include "shop_00.h"

/* func_801E2C18 */
MATCH void Menu_EquipStatPanel(void) {
    g_ShopEquipStatSteps[g_UiPanelCurrent->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    Menu_DrawEquipStatWindow(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy, ((u8*)g_CharSlot)[g_PartyFieldOrder[g_UiPanelCurrent->unk_0A]], g_UiPanelCurrent->unk_0B, g_UiPanelCurrent->unk_0C);
}
