#include "battle_15.h"

/* func_800A4294 */
MATCH s16 Battle_RollHpDamage(s32 divisor) {
    u32 mode;
    u16 base;
    u16 type_mask;
    s32 mod;
    u16 element_mask;
    u32 battler;

    mode = (*(u8*)&g_Battle.active_battler);
    if (mode < 3u) {
        base = g_Game.members[mode].chr.hp;
    } else {
        base = ENEMY_COMBATANT(mode).hp;
    }
    type_mask    = D_801CA71C[g_Battle.action_id].mask;
    mod          = 100;
    element_mask = type_mask & ELEM_ALL;
    if ((type_mask & (ELEM_FIRE | ELEM_FROST | ELEM_ELECTRIC | ELEM_EARTH | ELEM_WIND)) != 0u) {
        mod = Battle_GetFireResistance((*(u8*)&g_Battle.target), element_mask);
    }
    mod     = (((base / divisor) * D_800B498C[RANDOM_MASK(7)]) * mod) / 10000;
    battler = (*(u8*)&g_Battle.target);
    base    = BATTLER_IS_PLAYER(battler);
    if (base) {
        if (g_Game.members[battler].u.turn.damage_flags.volatile_value & BATTLER_DAMAGE_IMMUNE) {
            return 0;
        }
    } else {
        if (ENEMY_COMBATANT(battler).turn.damage_flags.value & BATTLER_DAMAGE_IMMUNE) {
            return 0;
        }
    }
    return mod;
}
