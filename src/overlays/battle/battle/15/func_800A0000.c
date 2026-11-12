#include "battle_15.h"

MATCH void func_800A0000(void) {
    s32 index;
    u8  flags;

    func_800A3F28();
    index = g_Battle.target - 3;
    if (g_BattleEnemyBattlers[index & BYTE_MASK].drops[0].rate != 0) {
        flags = g_BattleEnemyBattlers[index & BYTE_MASK].drops[0].flags;
        if (!(flags & 0x1)) {
            g_BattleEnemyBattlers[index & BYTE_MASK].drops[0].flags = flags | 0x1;
            g_BattleEnemyBattlers[index & BYTE_MASK].drops[0].rate += 2;
        }
    }
    if (g_BattleEnemyBattlers[index & BYTE_MASK].drops[1].rate != 0) {
        flags = g_BattleEnemyBattlers[index & BYTE_MASK].drops[1].flags;
        if (!(flags & 0x1)) {
            g_BattleEnemyBattlers[index & BYTE_MASK].drops[0x1].flags = flags | 1;
            g_BattleEnemyBattlers[index & BYTE_MASK].drops[1].rate += 1;
        }
    }
    if (g_BattleEnemyBattlers[index & BYTE_MASK].drops[0].rate >= 8U) {
        g_BattleEnemyBattlers[index & BYTE_MASK].drops[0].rate = 7;
    }
    if (g_BattleEnemyBattlers[index & BYTE_MASK].drops[1].rate >= 8U) {
        g_BattleEnemyBattlers[index & BYTE_MASK].drops[1].rate = 7;
    }
}
