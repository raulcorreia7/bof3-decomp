#include "battle_15.h"

/* dispatches the panel handler selected by the panel-task byte at
 * +3, then forwards the task's character/coordinates/state fields to the
 * panel renderer.
 */
MATCH void func_800B232C(void) {
    D_800B6E40[BATTLE_PANEL_TASK->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    func_800B3324(((u8*)g_CharSlot)[g_PartyBattleOrder[g_UiPanelCurrent->unk_0C]], (u16)g_UiPanelCurrent->pos.vx, (u16)g_UiPanelCurrent->pos.vy, ((s32*)g_UiPanelCurrent)[8], BATTLE_PANEL_TASK->cursor,
                  g_UiPanelCurrent);
}
