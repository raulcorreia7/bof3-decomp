#include "battle_15.h"

MATCH void func_8009EDB4(void) {
    volatile u16* flags;
    u16           flag_value;
    u32           action;
    s32           slot;
    s32           enemy_slot;
    u8            battler_index;
    u8            selection_type;
    s16           result;
    volatile u16* counter;
    u16           raw;
    u8            level;

    flags      = &g_Battle.flags;
    flag_value = *flags;
    /* FAKE: non-volatile alias of g_Battle.active_battler; the volatile read emits an andi
     * after lbu that retail does not carry. */
    slot       = g_Battle.active_battler;
    *flags     = flag_value | BATTLE_STATE_DAMAGE_APPLIED;
    if (slot < 3u) {
        action = g_Characters[g_CharSlot[g_Game.members[slot].chr.character_id]].base.power;
    } else {
        enemy_slot = slot - 3;
        action     = g_BattleEnemyBattlers[enemy_slot].base.power;
    }
    raw = D_801EC310;
    if (((raw >> 1) + 0x1E) >= 0x65) {
        level                         = 0x64;
        g_BattleCalcStats[1].accuracy = level;
    } else {
        level                         = ((raw >> 1) + 0x1E);
        g_BattleCalcStats[1].accuracy = level;
    }
    counter  = &D_801EC30C;
    *counter = 0;
    Char_AddStat(counter, action + (g_BattleCalcStats[1].defense));
    battler_index                     = g_Battle.active_battler;
    selection_type                    = g_Battle.target;
    result                            = Battle_CalcDamage(battler_index, selection_type, BATTLE_ELEMENT_FROM_WEAPON);
    g_Battle.target_record->hp_change = result;
}
