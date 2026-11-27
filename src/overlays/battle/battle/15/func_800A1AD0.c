#include "battle_15.h"

MATCH void func_800A1AD0(void) {
    u16 index;

    g_Battle.target_record->target_flags = 2;
    /* FAKE: the block keeps this statement in place; without it the match is 88.89%. */
    do {
        index = g_BattleActionId;
        ;
    } while (0);
    g_Battle.target_record->ap_change = Battle_RollActionDamage(g_BattleActiveBattler, *(u8*)(void*)&g_Battle.target, g_Abilities[index].power, 1);
}
