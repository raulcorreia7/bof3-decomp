#include "battle_03.h"

MATCH void func_801DDAF0(void) {
    PartyBattler*          work_a;
    volatile PartyBattler* work_b;
    u32                    index;

    index                               = Battle_AllocEffect(0u, 6u) & BYTE_MASK;
    work_a                              = g_Task;
    g_BattleEffects[index].unk_09       = 0u;
    work_b                              = g_Task;
    g_BattleEffects[index].target.party = work_a;
    g_BattleEffects[index].pos.x        = work_b->pos.x;
    g_BattleEffects[index].pos.y        = work_b->pos.y;
    g_BattleEffects[index].pos.z.raw    = work_b->pos.z.raw;
}
