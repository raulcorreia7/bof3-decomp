#include "boss001_13.h"

MATCH void Boss_EndBattle(void) {
    Battle_ShowActorEntry(6);
    Battle_CopyActorEntry(6, (PartyMember*)g_BattleEnemyBattlers, 1);
    SELF_SET(func_800AC754(6));
    Area_SceneSelectRecord(0x5F);
    SELF(PartyMember)->unk_2A = 0;
    SELF(PartyMember)->unk_48 = 0;
    Script_Select(1);
    SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    Battle_ShowActorEntry(7);
    Battle_CopyActorEntry(7, (PartyMember*)&g_BattleEnemyBattlers[1], 1);
    SELF_SET(func_800AC754(7));
    Area_SceneSelectRecord(0x5F);
    SELF(PartyMember)->unk_2A = 0;
    SELF(PartyMember)->unk_48 = 0;
    Script_Select(0);
    SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[1].unk_58;
    SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[1].unk_5A;
}
