#include "battle_15.h"

MATCH void func_8009F0A4(void) {
    volatile u16* flags;
    u16           flag_value;
    u32           action;
    s32           slot;
    s32           row;
    /* FAKE: pin the delta counter to retail a1. */
    FAKE_REG(u16, delta_raw, "a1");
    u8            battler_index;
    u8            selection_kind;
    s16           result;
    volatile u16* counter;
    /* FAKE: pin the counter sample to retail v0. */
    FAKE_REG(u16, raw, "v0");
    /* FAKE: pin the clamped level to retail v0. */
    FAKE_REG(u8, level, "v0");

    flags      = &g_Battle.state;
    flag_value = *flags;
    /* FAKE: non-volatile alias of g_Battle.active_battler; the volatile read emits an andi
     * after lbu that retail does not carry. */
    slot       = (*(u8*)&g_Battle.active_battler);
    *flags     = flag_value | BATTLE_STATE_DAMAGE_APPLIED;
    if (slot < 3u) {
        action = *(u16*)((u8*)&g_Characters[0].base.power + (g_CharSlot[g_Game.members[slot].chr.character_id] * 0xA4));
    } else {
        row    = slot - 3;
        action = g_BattleEnemyBattlers[row].base.power;
    }
    raw = D_801EC310;
    if (((raw >> 1) + 0x1E) >= 0x65) {
        level = 0x64;
    } else {
        level = ((raw >> 1) + 0x1E);
    }
    D_801EC324 = level;
    /* FAKE: keep the level store ahead of the counter store. */
    FAKE_BARRIER();
    delta_raw = D_801EC310;
    counter   = &D_801EC30C;
    *counter  = 0;
    Char_AddStat(counter, action + delta_raw);
    battler_index  = g_Battle.active_battler;
    selection_kind = g_Battle.target;
    /* FAKE: keeps the 0xFFFF load in the jal delay slot. */
    FAKE_BARRIER();
    result                            = Battle_CalcDamage(battler_index, selection_kind, BATTLE_ELEMENT_FROM_WEAPON);
    g_Battle.target_record->hp_change = result;
}
