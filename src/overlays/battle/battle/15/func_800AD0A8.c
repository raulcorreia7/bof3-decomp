#include "battle_15.h"

MATCH void func_800AD0A8(s32 enemy_index, s32 unit_index) {
    switch (BATTLE_WORK->facing) {
        case 0:
            g_BattleEnemyBattlers[(enemy_index & 0xFF)].unk_E2 = MEM_PTR(u8, 0x800E40BDu)[(unit_index & 0xFFFF) * 0x88];
            g_BattleEnemyBattlers[(enemy_index & 0xFF)].unk_E3 = MEM_PTR(u8, 0x800E40BFu)[(unit_index & 0xFFFF) * 0x88];
            break;
        case 1:
            g_BattleEnemyBattlers[(enemy_index & 0xFF)].unk_E2 =
                -MEM_PTR(u8, 0x800E40BDu)[(unit_index & 0xFFFF) * 0x88];
            g_BattleEnemyBattlers[(enemy_index & 0xFF)].unk_E3 = MEM_PTR(u8, 0x800E40BFu)[(unit_index & 0xFFFF) * 0x88];
            break;
        case 2:
            g_BattleEnemyBattlers[(enemy_index & 0xFF)].unk_E2 =
                -MEM_PTR(u8, 0x800E40BCu)[(unit_index & 0xFFFF) * 0x88];
            g_BattleEnemyBattlers[(enemy_index & 0xFF)].unk_E3 = MEM_PTR(u8, 0x800E40BEu)[(unit_index & 0xFFFF) * 0x88];
            break;
        case 3:
            g_BattleEnemyBattlers[(enemy_index & 0xFF)].unk_E2 = MEM_PTR(u8, 0x800E40BCu)[(unit_index & 0xFFFF) * 0x88];
            g_BattleEnemyBattlers[(enemy_index & 0xFF)].unk_E3 = MEM_PTR(u8, 0x800E40BEu)[(unit_index & 0xFFFF) * 0x88];
            break;
    }
}
