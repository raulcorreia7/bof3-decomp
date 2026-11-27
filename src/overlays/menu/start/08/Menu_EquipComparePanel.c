#include "start_08.h"

/* func_801EA50C */
MATCH void Menu_EquipComparePanel(void) {
    g_MenuStartEquipCompareSteps[g_UIPanelCurrent->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    Menu_DrawEquipCompareWindow(((u8*)g_CharSlot)[g_PartyFieldOrder[g_UIPanelCurrent->unk_0C]], (u16)g_UIPanelCurrent->pos.vx, (u16)g_UIPanelCurrent->pos.vy, (u8*)g_UIPanelCurrent->item_table,
                                g_UIPanelCurrent->flags, g_UIPanelCurrent);
}
