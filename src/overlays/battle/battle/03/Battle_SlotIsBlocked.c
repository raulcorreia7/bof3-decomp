#include "battle_03.h"

/* func_801DB524 */
MATCH u8 Battle_SlotIsBlocked(u32 slot) {
    u32 index;
    u32 subindex;
    u32 offset;

    index = slot & BYTE_MASK;
    if (index < 3u) {
        offset = index * 320u;
        if ((g_Game.members[index].header.flags & PARTY_MEMBER_FLAG_OCCUPIED) == 0) {
            return true;
        }
        if (HAS_STATUS(g_Game.members[index], STATUS_KO)) {
            return true;
        }
    } else {
        subindex = (slot - 3u) & BYTE_MASK;
        offset   = subindex * 280u;
        if ((g_BattleEnemyBattlers[subindex].header.flags & 0x1u) == 0u) {
            return true;
        }
        if ((g_BattleEnemyBattlers[subindex].status & STATUS_KO) != 0u) {
            return true;
        }
    }
    return false;
}
