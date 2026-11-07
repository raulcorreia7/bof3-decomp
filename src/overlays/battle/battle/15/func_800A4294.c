#include "battle_15.h"

MATCH s16 func_800A4294(s32 input_kind) {
    u32 mode;
    u16 base;
    u16 kind_mask;
    s32 mod;
    u16 element_mask;
    u32 battler;

    mode = (*(u8*)&g_BattleActiveBattler);
    if (mode < 3u) {
        base = g_BattlePartyBattlers[mode].chr.hp;
    } else {
        base = ENEMY_COMBATANT(mode).hp;
    }
    kind_mask    = D_801CA71C[g_BattleActionId].mask;
    mod          = 100;
    element_mask = kind_mask & 0x1FF;
    if ((kind_mask & 0x1Fu) != 0u) {
        mod = func_800A2AE0((*(u8*)&g_BattleTarget), element_mask);
    }
    mod     = (((base / input_kind) * D_800B498C[RANDOM_MASK(7)]) * mod) / 10000;
    battler = (*(u8*)&g_BattleTarget);
    base    = BATTLER_IS_PLAYER(battler);
    if (base) {
        if (g_BattlePartyBattlers[battler].turn.damage_flags.volatile_value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
            return 0;
        }
    } else {
        if (ENEMY_COMBATANT(battler).turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
            return 0;
        }
    }
    return mod;
}
