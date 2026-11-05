#include "start_08.h"

MATCH void func_801EA50C(void) {
    D_801ED58C[g_MenuPanelTaskCurrent->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    func_801DE5D4(((u8*)g_CharSlot)[D_80144F5A[g_MenuPanelTaskCurrent->unk_0C]], g_MenuPanelTaskCurrent->x,
                  g_MenuPanelTaskCurrent->y, g_MenuPanelTaskCurrent->item_table, g_MenuPanelTaskCurrent->flags,
                  g_MenuPanelTaskCurrent);
}
