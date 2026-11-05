#include "battle_03.h"

/* func_801DB524 */
MATCH u8 Battle_SlotIsBlocked(u32 slot) {
    u32 index;
    u32 subindex;
    u32 offset;

    index = slot & BYTE_MASK;
    if (index < 3u) {
        offset = index * 320u;
        if ((g_BattlePartyBattlers[index].flags & PARTY_BATTLER_FLAG_OCCUPIED) == 0) {
            return true;
        }
        if (HAS_STATUS(g_BattlePartyBattlers[index], STATUS_KO)) {
            return true;
        }
    } else {
        subindex = (slot - 3u) & BYTE_MASK;
        offset   = subindex * 280u;
        if ((D_801EB630[subindex].flags & 1u) == 0u) {
            return true;
        }
        if ((D_801EB630[subindex].status_82 & STATUS_KO) != 0u) {
            return true;
        }
    }
    return false;
}
