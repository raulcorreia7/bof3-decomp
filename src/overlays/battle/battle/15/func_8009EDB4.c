#include "battle_15.h"

MATCH void func_8009EDB4(void) {
    volatile u16* flags;
    u16           flag_value;
    u32           action;
    s32           slot;
    s32           row;
    /* FAKE: pin the delta counter to retail a1. */
    MATCH_REG(u16, delta_raw, "a1");
    u8            battler_index;
    u8            selection_kind;
    s16           result;
    volatile u16* counter;
    /* FAKE: pin the counter sample to retail v0. */
    MATCH_REG(u16, raw, "v0");
    /* FAKE: pin the halved counter to retail v1. */
    MATCH_REG(s32, shifted, "v1");
    /* FAKE: pin the clamped level to retail v0. */
    MATCH_REG(u8, level, "v0");

    flags      = &g_BattleState;
    flag_value = *flags;
    /* FAKE: non-volatile alias of g_BattleActiveBattler; the volatile read emits an andi
     * after lbu that retail does not carry. */
    slot       = (*(u8*)&g_BattleActiveBattler);
    *flags     = flag_value | BATTLE_STATE_DAMAGE_APPLIED;
    if (slot < 3u) {
        action = *(u16*)((u8*)&g_Characters[0].base_stats.power +
                         (g_CharSlot[D_80145F09[slot * BATTLE_PARTY_STRIDE]] * 0xA4));
    } else {
        row    = slot - 3;
        action = *(u16*)((u8*)D_801EB6F4 + row * BATTLE_ENEMY_STRIDE);
    }
    raw     = D_801EC310;
    shifted = raw >> 1;
    if ((shifted + 0x1E) >= 0x65) {
        level = 0x64;
    } else {
        level = (u8)(shifted + 0x1E);
    }
    D_801EC324 = level;
    /* FAKE: keep the level store ahead of the counter store. */
    MATCH_BARRIER();
    delta_raw = D_801EC30E;
    counter   = &D_801EC30C;
    *counter  = 0;
    Char_AddStat(counter, action + delta_raw);
    battler_index  = g_BattleActiveBattler;
    selection_kind = g_BattleTarget;
    /* FAKE: keeps the 0xFFFF load in the jal delay slot. */
    MATCH_FAKE_BARRIER();
    result                          = Battle_CalcDamage(battler_index, selection_kind, 0xFFFF);
    ((s16*)g_BattleTargetRecord)[2] = result;
}
