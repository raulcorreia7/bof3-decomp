#include "battle_03.h"

/* Four state handlers; the binary keeps the table at this address and no
 * header declares it. */
typedef void (*BattlePanelFunc)(void);

/* 0x118-byte enemy work rows; the rows are anchors that the code addresses by
 * byte offset. The row's action points and cap are read through the
 * EnemyBattler record. */

/* advances the battle menu panel: dispatches the state handler,
 * copies the selected enemy's figures and the panel fields into the panel
 * record, closes the panel when the slot becomes blocked, and toggles the
 * enemy row's 0x2000 flag from the row's shutter counters.
 */
/* func_801E960C */
MATCH void Battle_UpdateMenuPanel(void) {
    BattlePanelTask* task;
    BattlePanelTask* panel;
    u8*              row;
    u32              slot;
    u32              offset;
    u16              flags;
    BattlePanelFunc  handlers[4];

    memcpy(handlers, D_801D0FD0, sizeof(handlers));

    handlers[BATTLE_PANEL_TASK->state]();

    task = BATTLE_PANEL_TASK;
    row  = D_801EB35C + task->cell_0A.slot * 0x118;
    func_801EA1E0(&task->ratio, (row + 0x2C), &task->max_hp, &task->hp, (row + 0x20), &task->cursor, &task->pad_16[2], &task->unk_08);

    if (Battle_SlotIsBlocked(BATTLE_PANEL_TASK->cell_0A.slot) != 0) {
        panel = BATTLE_PANEL_TASK;
        if (panel->cursor == 0) {
            panel->state = 3;
        }
    }

    slot   = BATTLE_PANEL_TASK->cell_0A.slot - 3;
    offset = slot * 0x118;
    if (g_BattleEnemyBattlers[slot].hp < (g_BattleEnemyBattlers[slot].stats.max_hp >> 2)) {
        /* Retail reads the status through its own address, not the EnemyBattler row. */
        flags = *(u16*)(D_801EB6B2 + offset) | 0x2000;
    } else {
        flags = *(u16*)(D_801EB6B2 + offset) & 0xDFFF;
    }
    *(u16*)(D_801EB6B2 + offset) = flags;
}
