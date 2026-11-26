#include "battle_03.h"

/* Queued-slot entries (stride 0x78). */

/* func_801E590C */
MATCH u32 Battle_AllocEffect(u32 mode, u32 effect_type) {
    u8 index;

    for (index = 0u; index < BATTLE_EFFECT_COUNT; index++) {
        if ((g_BattleEffects[index].header.flags & 0x1u) == 0u) {
            g_BattleEffects[index].header.flags |= 1u;
            g_BattleEffects[index].unk_06      = mode;
            g_BattleEffects[index].effect_type = effect_type;
            return index;
        }
    }
    return 0xFFu;
}
