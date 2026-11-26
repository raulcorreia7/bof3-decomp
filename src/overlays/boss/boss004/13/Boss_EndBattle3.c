#include "boss004_13.h"

MATCH void Boss_EndBattle3(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        Battle_ShowActorEntry(4);
        Battle_ShowActorEntry(5);
        return;
    }
    Battle_ShowActorEntry(4);
    Battle_CopyActorEntry(4, (PartyMember*)g_BattleEnemyBattlers, 1);
    SELF_SET(func_800AC754(4));
    Area_SceneSelectRecord(0x5F);
    SELF(PartyMember)->unk_48 = 0;
    SELF(PartyMember)->unk_2A = 1;
    Script_Select(1);
    SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    Battle_ShowActorEntry(5);
    Battle_CopyActorEntry(5, (PartyMember*)&g_BattleEnemyBattlers[1], 1);
    SELF_SET(func_800AC754(5));
    Area_SceneSelectRecord(0x5F);
    SELF(PartyMember)->unk_48 = 0;
    SELF(PartyMember)->unk_2A = 1;
    Script_Select(1);
    SELF(PartyMember)->unk_58      = g_BattleEnemyBattlers[1].unk_58;
    SELF(PartyMember)->unk_5A      = g_BattleEnemyBattlers[1].unk_5A;
    SELF(PartyMember)->pos.x.fixed = g_BattleEnemyBattlers[1].pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = g_BattleEnemyBattlers[1].pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed = g_BattleEnemyBattlers[1].pos.z.fixed;
}
