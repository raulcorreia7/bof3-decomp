#include "battle_03.h"

MATCH u8 func_801DB2F8(u32 battler_index) {
    u32 index;
    u32 subindex;
    u32 offset;

    index = battler_index & 0xFF;
    if (index < 3u) {
        offset = index * 320u;
        if (!ACTOR_IN_USE(g_BattlePartyBattlers[index])) {
            return false;
        }
        if (HAS_STATUS(g_BattlePartyBattlers[index], 0x4944u)) {
            return false;
        }
    } else {
        subindex = (battler_index - 3u) & 0xFF;
        offset   = subindex * 280u;
        if ((g_BattleEnemyBattlers[subindex].header.flags & 1u) == 0u) {
            return false;
        }
        if ((g_BattleEnemyBattlers[subindex].status & 0x4144u) != 0u) {
            return false;
        }
    }
    return true;
}
