#include "boss004_13.h"

MATCH void Boss_EndBattle3(void) {
    if (g_BattleResult & 1) {
        func_800AC844(4U);
        func_800AC844(5U);
        return;
    }
    func_800AC844(4U);
    func_800AC870(4, (PartyBattler *) g_BattleEnemyBattlers, 1);
    ((PartyBattler *)g_Task) = func_800AC754(4U);
    Area_FindSceneRecord(0x5F);
    ((PartyBattler *)g_Task)->unk_48 = 0;
    ((PartyBattler *)g_Task)->unk_2A = 1;
    Actor_SelectScript(1U);
    ((PartyBattler *)g_Task)->unk_58 = D_801EB688;
    ((PartyBattler *)g_Task)->unk_5A = D_801EB68A;
    func_800AC844(5U);
    func_800AC870(5, (PartyBattler *) (g_BattleEnemyBattlers + 0x118), 1);
    ((PartyBattler *)g_Task) = func_800AC754(5U);
    Area_FindSceneRecord(0x5F);
    ((PartyBattler *)g_Task)->unk_48 = 0;
    ((PartyBattler *)g_Task)->unk_2A = 1;
    Actor_SelectScript(1U);
    ((PartyBattler *)g_Task)->unk_58 = D_801EB7A0;
    ((PartyBattler *)g_Task)->unk_5A = D_801EB7A2;
    ((PartyBattler *)g_Task)->pos.x.fixed = D_801EB77C;
    ((PartyBattler *)g_Task)->pos.y.fixed = D_801EB780;
    ((PartyBattler *)g_Task)->pos.z.fixed = D_801EB784;
}
