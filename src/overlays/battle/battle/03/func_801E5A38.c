#include "battle_03.h"

/* Queued-slot entries (stride 0x78) whose key-state bytes are cleared. */

MATCH void func_801E5A38(void) {
    u8 index;

    index = 0u;
    do {
        u32 n;

        n = index;
        index += 1u;
        g_BattleEffects[n].flags         = 0u;
        g_BattleEffects[n].handler_index = 0u;
        g_BattleEffects[n].unk_06        = 0u;
        g_BattleEffects[n].mode          = 0u;
        g_BattleEffects[n].step          = 0u;
        g_BattleEffects[n].unk_03        = 0u;
        g_BattleEffects[n].unk_04        = 0u;
        g_BattleEffects[n].unk_48        = 0u;
        g_BattleEffects[n].unk_5D        = 0u;
        g_BattleEffects[n].unk_5E        = 0u;
        g_BattleEffects[n].unk_5F        = 0u;
    } while (index < BATTLE_EFFECT_COUNT);
}
