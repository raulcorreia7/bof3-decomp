#include "shop_00.h"

/* func_801E2C18 */
MATCH void Menu_EquipStatPanel(void) {
    g_ShopEquipStatSteps[g_UIPanelCurrent->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    Menu_DrawEquipStatWindow(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, ((u8*)g_CharSlot)[g_PartyFieldOrder[g_UIPanelCurrent->unk_0A]], g_UIPanelCurrent->unk_0B, g_UIPanelCurrent->unk_0C);
}
