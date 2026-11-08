#include "battle_15.h"

MATCH void func_8009F884(void) {
    u8  mode;
    u16 base;
    u16 flags;
    s16 record;
    u8  battler_index;
    u8  selection_kind;

    mode = LOBU(g_BattleTarget);
    if (mode < 3u) {
        base  = g_Game.members[mode].chr.hp;
        flags = g_Game.members[mode].chr.status;
    } else {
        base  = ENEMY_COMBATANT(mode).hp;
        flags = ENEMY_COMBATANT(mode).status;
    }
    battler_index  = g_BattleActiveBattler;
    selection_kind = g_BattleTarget;
    /* FAKE: keeps the 2 load in the jal delay slot. */
    MATCH_FAKE_BARRIER();
    ((volatile BattleTurn*)g_BattleTargetRecord)->hp_change =
        Battle_CalcDamage(battler_index, selection_kind, ELEM_FROST);
    record = g_BattleTargetRecord->hp_change;
    if (record < base && !(flags & STATUS_SLEEPING) && record != 0) {
        func_800A4238(0x40);
    }
}
