#include "battle_03.h"

MATCH u8 func_801DB2F8(u32 battler_index) {
    u32 index;
    u32 subindex;
    u32 offset;

    index = battler_index & BYTE_MASK;
    if (index < 3u) {
        offset = index * 320u;
        if (!ACTOR_IN_USE(g_Game.members[index])) {
            return false;
        }
        if (HAS_STATUS(g_Game.members[index], 0x4944u)) {
            return false;
        }
    } else {
        subindex = (battler_index - 3u) & BYTE_MASK;
        offset   = subindex * 280u;
        if ((g_BattleEnemyBattlers[subindex].header.flags & 0x1u) == 0u) {
            return false;
        }
        if ((g_BattleEnemyBattlers[subindex].status & (STATUS_PARALYZED | STATUS_SLEEPING | STATUS_UNK_8 | STATUS_KO)) != 0u) {
            return false;
        }
    }
    return true;
}
