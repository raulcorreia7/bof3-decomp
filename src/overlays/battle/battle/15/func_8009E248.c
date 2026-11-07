#include "battle_15.h"

extern u16 D_801EB6D0[][0x8C];

/* Shows the selected battler's damage step and adjusts the HP bar.
 */
/* nonmatching unmeasured: tried the first draft rewritten with typed HP record views and flag checks. resume: close the
 * +0x0 branch (early-return shape). */
#ifdef NON_MATCHING
NON_MATCHING void func_8009E248(void) {
    s32 id;
    s32 enemy;
    s16 hp_bar;
    u16 hp;

    id = g_BattleActiveBattler;
    if (!(func_800A3A10(id, g_BattleTarget) & BYTE_MASK)) {
        if (BATTLER_IS_PLAYER(g_BattleTarget)) {
            if (!(g_BattlePartyBattlers[g_BattleTarget].turn.damage_flags.volatile_value &
                  COMBATANT_FLAG_DAMAGE_IMMUNE)) {
                hp = g_BattlePartyBattlers[g_BattleTarget].chr.hp;
            } else {
                hp = 0;
            }
        } else {
            enemy = g_BattleTarget - 3;
            if (g_BattleEnemyBattlers[enemy].turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
                hp = 0;
            } else {
                hp = D_801EB6C4[enemy][0];
            }
        }
        hp_bar                          = hp / 5;
        g_BattleTargetRecord->hp_change = hp_bar;
        g_BattleAction->unk_08          = 1;
        if (id < 3) {
            if (g_BattlePartyBattlers[id].chr.stats.max_hp < g_BattlePartyBattlers[id].chr.hp + hp_bar) {
                g_BattleAction->unk_08 |= 4;
            }
            func_800AAC88((s16)-Char_AddPoints(&g_BattlePartyBattlers[id].chr.hp,
                                               g_BattlePartyBattlers[id].chr.stats.max_hp, hp_bar),
                          id);
        } else {
            enemy = id - 3;
            if (D_801EB6D0[enemy][0] < D_801EB6C4[enemy][0] + hp_bar) {
                g_BattleAction->unk_08 |= 4;
            }
            func_800AAC88((s16)-Char_AddPoints(&D_801EB37C[id][0], D_801EB6D0[enemy][0], hp_bar), id);
        }
        g_BattleAction->unk_08 = 0;
        return;
    }
    g_BattleTargetRecord->target_flags = 1;
}
#else
INCLUDE_ASM(func_8009E248);
#endif
