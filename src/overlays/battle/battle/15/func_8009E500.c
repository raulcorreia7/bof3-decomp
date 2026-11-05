#include "battle_15.h"

/* Prepares the selected battler's damage preview: reads the damage cap from the player or enemy row into the
 * 0x801463A0 slot 3, marks the action state, then passes the row limit and the cap to the damage routine after growing
 * the preview when it exceeds the limit. */
/* nonmatching unmeasured: tried frame 0x28 vs 0x18: the cached delta/limit locals spill while the retail keeps them in
 * registers; branch layout now bne to the tail store. resume: drive both halves from one u32 row index and pass the row
 * addresses as non-volatile u16 pointers. */
#ifdef NON_MATCHING
NON_MATCHING void func_8009E500(void) {
    s16 delta;
    u16 limit;
    if (!(func_800A3A10(g_BattleActiveBattler, g_BattleTarget) & BYTE_MASK)) {
        if (BATTLER_IS_PLAYER(g_BattleTarget)) {
            if (g_BattlePartyBattlers[g_BattleTarget].damage_flags.volatile_value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
                g_BattleTargetRecord[3] = 0;
            } else {
                g_BattleTargetRecord[3] = D_80145F1A[g_BattleTarget * 160] / 5;
            }
        } else if (ENEMY_COMBATANT(g_BattleTarget).damage_flags & COMBATANT_FLAG_DAMAGE_IMMUNE) {
            g_BattleTargetRecord[3] = 0;
        } else {
            g_BattleTargetRecord[3] = D_801EB6C4[g_BattleTarget - 3][1] / 5;
        }
        g_BattleAction->unk_08  = 2;
        g_BattleTargetRecord[4] = 2;
        delta                   = g_BattleTargetRecord[3];
        if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
            limit = D_80145F1A[g_BattleActiveBattler * 160 + 4];
            if (limit < D_80145F1A[g_BattleActiveBattler * 160] + delta) {
                g_BattleAction->unk_08 |= 8;
            }
            func_800AAEBC(-Char_AddPoints(&D_80145F1A[g_BattleActiveBattler * 160], limit, delta),
                          g_BattleActiveBattler);
        } else {
            limit = D_801EB6C4[g_BattleActiveBattler - 3][7];
            if (limit < D_801EB6C4[g_BattleActiveBattler - 3][1] + delta) {
                g_BattleAction->unk_08 |= 8;
            }
            func_800AAEBC(-Char_AddPoints(&D_801EB6C4[g_BattleActiveBattler - 3][1], limit, delta),
                          g_BattleActiveBattler);
        }
        g_BattleAction->unk_08 = 0;
    } else {
        g_BattleTargetRecord[4] = 2;
    }
}
#else
INCLUDE_ASM(func_8009E500);
#endif
