#include "battle_03.h"

/* positions the panel task from the selected enemy row's base and
 * value offsets, draws it, then drops the panel when the active selection slot
 * disagrees with the panel's row.
 */
MATCH void func_801E99AC(void) {
    BattlePanelTask* panel;
    u8               row;
    s32              base;
    u8               kind;
    s32              adj;
    u16              y;
    u8               slot;

    panel         = BATTLE_PANEL_TASK;
    row           = panel->cell_0A.slot - 3;
    base          = g_BattleEnemyBattlers[row].unk_2E + g_BattleEnemyBattlers[row].panel_offset_x;
    kind          = g_BattleEnemyBattlers[row].unk_08;
    adj           = ((kind == 0) || (kind == 3)) ? D_801EAEA4[0] : D_801EAEA4[2];
    panel->x.half = base + adj;
    /* FAKE: retail keeps the second row scan after the x store. */
    MATCH_BARRIER();
    y                         = g_BattleEnemyBattlers[row].unk_30 + g_BattleEnemyBattlers[row].panel_offset_y + 0xC;
    BATTLE_PANEL_TASK->y.half = y;
    func_801D8690((s16)BATTLE_PANEL_TASK->x.half, (s16)y, BATTLE_PANEL_TASK->cell_0A.slot);
    if (g_Battle.selection_latch != 0) {
        slot = g_BattleActorTurn->command.target;
        if ((slot & 0xC0) == 0) {
            if (slot == BATTLE_PANEL_TASK->cell_0A.slot) {
                return;
            }
        } else if ((slot & 0x40) != 0) {
            return;
        }
    }
    func_801EA1A4();
}
