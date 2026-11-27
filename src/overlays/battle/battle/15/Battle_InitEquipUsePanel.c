#include "battle_15.h"

/* func_8009B160 */
MATCH void Battle_InitEquipUsePanel(void) {
    u8  one;
    u8  eight;
    u8* slot;
    u8  three;
    u8  entry_index;
    u8  tail_index;

    /* FAKE: the block steers regalloc */
    do {
        one   = 1;
        eight = 8;
        slot  = g_BattleMessageSlot;
        three = 3;
    } while (0);

    g_UiPanelTasks[18].panel  = eight;
    g_UiPanelTasks[18].active = one;
    g_UiPanelTasks[18].mode   = three;
    g_BattlePanelMode         = three;
    g_BattleEquipSlot         = 0;
    g_UiPanelTasks[18].unk_0B = 0xFF;
    entry_index               = slot[5];
    D_801485D8                = &s_BattleEquipment[0];
    g_UiPanelTasks[18].pos.vx = -0xAA;
    g_UiPanelTasks[18].pos.vy = 0x3F;
    g_UiPanelTasks[18].flags  = one;
    g_BattleChoicePhase       = 4;
    g_UiPanelTasks[18].unk_0C = entry_index;
    tail_index                = slot[5];
    g_UiPanelTasks[18].flags  = three;
    D_80148656                = tail_index;
}
