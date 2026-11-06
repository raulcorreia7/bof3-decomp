#include "battle_03.h"

MATCH s32 func_801DD59C(s32 amount) {
    u32 i;
    u32 index;

    i = 0;
    if (g_BattlePartyCount != 0u) {
        do {
            index = i & 0xFF;
            if (func_801DD704(index) != 0u) {
                if ((g_Characters[func_801DD7AC(g_BattlePartyBattlers[index].chr.character_id)].exp + amount) <=
                    0x98967Eu) {
                    g_Characters[func_801DD7AC(g_BattlePartyBattlers[index].chr.character_id)].exp += amount;
                } else {
                    g_Characters[func_801DD7AC(g_BattlePartyBattlers[index].chr.character_id)].exp = 0x98967F;
                }
            }
            i += 1u;
        } while ((i & 0xFF) < g_BattlePartyCount);
    }
    return amount;
}
