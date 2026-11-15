#include "battle_03.h"

MATCH void func_801E72F4(void) {
    PartyMember* scratch;

    g_Task->header.flags = (g_BattleEffectBattler->header.flags | ACTOR_FLAG_SEMI_TRANSPARENT);
    g_Task->unk_48       = g_BattleEffectBattler->unk_48;

    scratch          = g_Task;
    scratch->scale.x = g_BattleEffectBattler->scale.x;
    scratch->scale.y = g_BattleEffectBattler->scale.y;
    scratch->unk_58  = g_BattleEffectBattler->unk_58;
    scratch->unk_5A  = BATTLE_ACTIVE_WORK->unk_5A;
    scratch->unk_4B  = g_BattleEffectBattler->unk_4B;

    g_Task->unk_4A = g_BattleEffectBattler->unk_4A;
    g_Task->unk_49 = g_BattleEffectBattler->unk_49;

    scratch         = g_Task;
    scratch->unk_4C = BATTLE_ACTIVE_WORK->unk_4C;
    scratch->unk_50 = BATTLE_ACTIVE_WORK->unk_50;
    scratch->unk_54 = BATTLE_ACTIVE_WORK->unk_54;
    scratch->unk_27 = g_BattleEffectBattler->unk_27;

    g_Task->unk_28 = g_BattleEffectBattler->unk_28;
    g_Task->unk_2A = g_BattleEffectBattler->unk_2A;

    scratch              = g_Task;
    scratch->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    scratch->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    scratch->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;

    func_8014D290();
    if (!ACTOR_IN_USE(*g_BattleEffectBattler)) {
        Effect_Reset();
    }
    if (g_Battle.phase.mode != BATTLE_MODE_COMMANDS) {
        Effect_Reset();
    }
}
