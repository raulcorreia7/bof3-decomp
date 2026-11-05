#include "battle_15.h"

/* dispatches the panel handler selected by the panel-task byte at
 * +3, then forwards the task's character/coordinates/state fields to the
 * panel renderer.
 */
MATCH void func_800B232C(void) {
    D_800B6E40[BATTLE_PANEL_TASK->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    func_800B3324(((u8*)g_CharSlot)[D_80144F5D[BATTLE_PANEL_TASK->unk_0C]], ((u16*)g_MenuPanelTaskCurrent)[2],
                  ((u16*)g_MenuPanelTaskCurrent)[3], ((s32*)g_MenuPanelTaskCurrent)[8],
                  BATTLE_PANEL_TASK->cursor, g_MenuPanelTaskCurrent);
}
