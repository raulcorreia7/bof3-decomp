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

    D_801485B9                = eight;
    D_801485B8                = one;
    D_801485BA                = three;
    g_BattlePanelMode         = three;
    g_BattleEquipSlot         = 0;
    g_UiPanelTasks[18].unk_0B = 0xFF;
    entry_index               = slot[5];
    D_801485D8                = &s_BattleEquipment[0];
    D_801485BC                = -0xAA;
    D_801485BE                = 0x3F;
    D_801485C5                = one;
    g_BattleChoicePhase       = 4;
    g_UiPanelTasks[18].unk_0C = entry_index;
    tail_index                = slot[5];
    D_801485C5                = three;
    D_80148656                = tail_index;
}
