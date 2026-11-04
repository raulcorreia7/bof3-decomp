#include "battle_03.h"

MATCH void func_801DDAF0(void) {
    PartyBattler*          work_a;
    volatile PartyBattler* work_b;
    u32                    index;

    index                               = Battle_AllocEffect(0u, 6u) & BYTE_MASK;
    work_a                              = g_SpadWork;
    g_BattleEffects[index].unk_09       = 0u;
    work_b                              = g_SpadWork;
    g_BattleEffects[index].target.party = work_a;
    g_BattleEffects[index].unk_34       = work_b->coord_x_34;
    g_BattleEffects[index].unk_38       = work_b->coord_y_38;
    g_BattleEffects[index].word_3C.word = work_b->word_3C.word;
}
