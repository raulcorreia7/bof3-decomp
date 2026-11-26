#include "boss004_13.h"

MATCH void Boss_EndBattle(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        Battle_ShowActorEntry(0);
        Battle_ShowActorEntry(1);
        return;
    }
    Battle_ShowActorEntry(0);
    Battle_CopyActorEntry(0, (PartyMember*)g_BattleEnemyBattlers, 1);
    SELF_SET(func_800AC754(0));
    Area_SceneSelectRecord(0x5F);
    SELF(PartyMember)->unk_48 = 0;
    SELF(PartyMember)->unk_2A = 1;
    Script_Select(1);
    SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    Battle_ShowActorEntry(1);
    Battle_CopyActorEntry(1, (PartyMember*)&g_BattleEnemyBattlers[1], 1);
    SELF_SET(func_800AC754(1));
    Area_SceneSelectRecord(0x5F);
    SELF(PartyMember)->unk_48 = 0;
    SELF(PartyMember)->unk_2A = 1;
    Script_Select(1);
    SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[1].unk_58;
    SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[1].unk_5A;
}
