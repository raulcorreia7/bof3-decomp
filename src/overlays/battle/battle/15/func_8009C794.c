#include "battle_15.h"

extern u8 Battle_Unk0E1BitTest(volatile u8* entry, s32 bit_index);

MATCH s32 func_8009C794(s32 skip_slot, s32 row_index) {
    u8* slot;
    u8* battler;
    s32 row;
    s32 count;
    u8  index;

    count = 0;
    row   = row_index & 0xFF;
    do {
        index = (count & 0xFF);
        if (index != (skip_slot & 0xFF)) {
            slot    = MEM_PTR(u8, 0x800E4048u) + g_BattleEnemyBattlers[row].kind * 0x88u;
            battler = slot + index * 0x10u;
            if (battler[0x34] == 0x63) {
                return 0;
            }
            if (Battle_Unk0E1BitTest((volatile u8*)&g_BattleEnemyBattlers[row], index) == 0) {
                return 0;
            }
        }
        count++;
    } while ((count & 0xFF) < 4U);
    return 1;
}
