#include "start_08.h"

/* func_801EA50C */
MATCH void Menu_EquipComparePanel(void) {
    g_MenuStartEquipCompareSteps[g_UiPanelCurrent->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    Menu_DrawEquipCompareWindow(((u8*)g_CharSlot)[g_PartyFieldOrder[g_UiPanelCurrent->unk_0C]], (u16)g_UiPanelCurrent->pos.vx, (u16)g_UiPanelCurrent->pos.vy, (u8*)g_UiPanelCurrent->item_table,
                                g_UiPanelCurrent->flags, g_UiPanelCurrent);
}
