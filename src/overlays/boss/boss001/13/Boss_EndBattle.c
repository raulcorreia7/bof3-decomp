#include "boss001_13.h"

MATCH void Boss_EndBattle(void) {
    func_800AC844(6);
    func_800AC870(6, (PartyBattler*)D_801EB630, 1);
    g_SpadWork = (PartyBattler*)func_800AC754(6);
    Area_FindSceneRecord(0x5F);
    g_SpadWork->unk_2A = 0;
    g_SpadWork->unk_48 = 0;
    Actor_SelectScript(1);
    g_SpadWork->unk_58 = D_801EB630[0].unk_58;
    g_SpadWork->unk_5A = D_801EB630[0].unk_5A;
    func_800AC844(7);
    func_800AC870(7, (PartyBattler*)&D_801EB630[1], 1);
    g_SpadWork = (PartyBattler*)func_800AC754(7);
    Area_FindSceneRecord(0x5F);
    g_SpadWork->unk_2A = 0;
    g_SpadWork->unk_48 = 0;
    Actor_SelectScript(0);
    g_SpadWork->unk_58 = D_801EB630[1].unk_58;
    g_SpadWork->unk_5A = D_801EB630[1].unk_5A;
}
