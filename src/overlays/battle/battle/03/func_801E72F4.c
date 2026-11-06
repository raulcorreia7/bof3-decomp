#include "battle_03.h"

MATCH void func_801E72F4(void) {
    PartyBattler* scratch;

    g_Task->flags  = (D_801EB4E0->flags | ACTOR_FLAG_SEMI_TRANSPARENT);
    g_Task->unk_48 = D_801EB4E0->unk_48;

    scratch         = g_Task;
    scratch->unk_40 = D_801EB4E0->unk_40;
    scratch->unk_44 = D_801EB4E0->unk_44;
    scratch->unk_58 = D_801EB4E0->unk_58;
    scratch->unk_5A = BATTLE_ACTIVE_WORK->unk_5A;
    scratch->unk_4B = D_801EB4E0->unk_4B;

    g_Task->unk_4A = D_801EB4E0->unk_4A;
    g_Task->unk_49 = D_801EB4E0->unk_49;

    scratch         = g_Task;
    scratch->unk_4C = BATTLE_ACTIVE_WORK->unk_4C;
    scratch->unk_50 = BATTLE_ACTIVE_WORK->unk_50;
    scratch->unk_54 = BATTLE_ACTIVE_WORK->unk_54;
    scratch->unk_27 = D_801EB4E0->unk_27;

    g_Task->unk_28 = D_801EB4E0->unk_28;
    g_Task->unk_2A = D_801EB4E0->unk_2A;

    scratch              = g_Task;
    scratch->pos.x.fixed = D_801EB4E0->pos.x.fixed;
    scratch->pos.y.fixed = D_801EB4E0->pos.y.fixed;
    scratch->pos.z.fixed = D_801EB4E0->pos.z.fixed;

    func_8014D290();
    if (!ACTOR_IN_USE(*D_801EB4E0)) {
        func_801E5988();
    }
    if (g_BattleMode != 1) {
        func_801E5988();
    }
}
