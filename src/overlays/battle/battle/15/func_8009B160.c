#include "battle_15.h"

MATCH void func_8009B160(void) {
    u8  one;
    u8  eight;
    u8* slot;
    u8  three;
    u8  entry_index;
    u8  tail_index;

    /* FAKE: the order lock steers regalloc */
    FAKE_ORDER_LOCK_BEGIN
        one   = 1;
        eight = 8;
        slot  = g_BattleMessageSlot;
        three = 3;
    FAKE_ORDER_LOCK_END;

    D_801485B9          = eight;
    D_801485B8          = one;
    D_801485BA          = three;
    g_BattlePanelMode   = three;
    g_BattleItemRow     = 0;
    D_801485C3          = 0xFF;
    entry_index         = slot[5];
    D_801485D8          = &s_BattleEquipment[0];
    D_801485BC          = -0xAA;
    D_801485BE          = 0x3F;
    D_801485C5          = one;
    g_BattleChoicePhase = 4;
    D_801485C4          = entry_index;
    tail_index          = slot[5];
    D_801485C5          = three;
    D_80148656          = tail_index;
}
