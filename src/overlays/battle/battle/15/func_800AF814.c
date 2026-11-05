#include "battle_15.h"

MATCH void func_800AF814(u32 battler_index) {
    u8  index;
    u32 offset;

    index = battler_index & BYTE_MASK;
    if (Battle_SlotIsBlocked(index) & BYTE_MASK) {
        return;
    }
    if (index < 3) {
        offset = index * BATTLE_PARTY_STRIDE;
        if (!HAS_STATUS(g_BattlePartyBattlers[index], STATUS_POISONED)) {
            return;
        }
        GFX_AllocPaletteFade((u8*)g_BattlePartyBattlers + offset, -6, -0xA, 0, 0);
    } else {
        offset = (index - 3) * BATTLE_ENEMY_STRIDE;
        if ((ENEMY_COMBATANT(index).status & STATUS_POISONED) == 0) {
            return;
        }
        GFX_AllocPaletteFade(g_BattleEnemies + index * BATTLE_ENEMY_STRIDE, -6, -0xA, 0, 0);
    }
}
