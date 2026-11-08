#include "battle_15.h"

MATCH s32 func_8009C794(s32 skip_slot, s32 row_index) {
    u8* slot;
    u8* battler;
    s32 row;
    s32 count;
    u8  index;

    count = 0;
    row   = row_index & BYTE_MASK;
    do {
        index = (count & BYTE_MASK);
        if (index != (skip_slot & BYTE_MASK)) {
            slot    = MEM_PTR(u8, 0x800E4048u) + g_BattleEnemyBattlers[row].kind * 0x88u;
            battler = slot + index * 0x10u;
            if (battler[0x34] == 0x63) {
                return 0;
            }
            if (Battle_EnemyEventFired(&g_BattleEnemyBattlers[row], index) == 0) {
                return 0;
            }
        }
        count++;
    } while ((count & BYTE_MASK) < 4U);
    return 1;
}
