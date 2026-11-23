#include "battle_03.h"

/* positions the panel task from the selected enemy record's base and
 * value offsets, draws it, then drops the panel when the active selection slot
 * disagrees with the panel's slot.
 */
/* func_801E99AC */
MATCH void Battle_PlaceEnemyPanel(void) {
    BattlePanelTask* panel;
    u8               enemy_slot;
    s32              base;
    u8               type;
    s32              adj;
    u16              y;
    u8               slot;

    panel          = BATTLE_PANEL_TASK;
    enemy_slot     = panel->selection.slot - 3;
    base           = g_BattleEnemyBattlers[enemy_slot].screen_x + g_BattleEnemyBattlers[enemy_slot].panel_offset_x;
    type           = g_BattleEnemyBattlers[enemy_slot].unk_08;
    adj            = ((type == 0) || (type == 3)) ? D_801EAEA4[0] : D_801EAEA4[2];
    panel->x.value = base + adj;
    /* FAKE: retail keeps the second slot read after the x store. */
    FAKE_BARRIER();
    y                          = g_BattleEnemyBattlers[enemy_slot].screen_y + g_BattleEnemyBattlers[enemy_slot].panel_offset_y + 0xC;
    BATTLE_PANEL_TASK->y.value = y;
    Battle_DrawEnemyPanel((s16)BATTLE_PANEL_TASK->x.value, (s16)y, BATTLE_PANEL_TASK->selection.slot);
    if (g_Battle.selection_latch != 0) {
        slot = g_BattleActorTurn->command.target;
        if ((slot & 0xC0) == 0) {
            if (slot == BATTLE_PANEL_TASK->selection.slot) {
                return;
            }
        } else if ((slot & 0x40) != 0) {
            return;
        }
    }
    Battle_DimPanel();
}
