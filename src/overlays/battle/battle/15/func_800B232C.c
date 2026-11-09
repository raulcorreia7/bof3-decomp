#include "battle_15.h"

/* dispatches the panel handler selected by the panel-task byte at +3. */
MATCH void func_800B232C(void) {
    D_800B6E40[BATTLE_PANEL_TASK->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    func_800B3324(((u8*)g_CharSlot)[g_PartyBattleOrder[g_MenuCurrentPanel->unk_0C]], g_MenuCurrentPanel->pos.x,
                  g_MenuCurrentPanel->pos.y, ((s32*)g_MenuCurrentPanel)[8], BATTLE_PANEL_TASK->cursor,
                  g_MenuCurrentPanel);
}
