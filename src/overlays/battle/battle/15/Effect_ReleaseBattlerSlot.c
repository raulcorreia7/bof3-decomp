#include "battle_15.h"

/* func_800AF814 */
MATCH void Effect_ReleaseBattlerSlot(u32 battler_index) {
    u8  index;
    u32 offset;

    index = battler_index & BYTE_MASK;
    if (Battle_SlotIsBlocked(index) & BYTE_MASK) {
        return;
    }
    if (index < 3) {
        offset = index * BATTLE_PARTY_STRIDE;
        if (!HAS_STATUS(g_Game.members[index], STATUS_POISONED)) {
            return;
        }
        GFX_AllocPaletteFade((u8*)g_Game.members + offset, -6, -0xA, 0, 0);
    } else {
        offset = (index - 3) * BATTLE_ENEMY_STRIDE;
        if ((ENEMY_COMBATANT(index).status & STATUS_POISONED) == 0) {
            return;
        }
        GFX_AllocPaletteFade(g_BattleEnemies + index * BATTLE_ENEMY_STRIDE, -6, -0xA, 0, 0);
    }
}
