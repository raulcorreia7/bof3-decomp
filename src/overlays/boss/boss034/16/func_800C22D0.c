#include "boss034_16.h"

MATCH void func_800C22D0(void) {
    Battle_ShowActorEntry(0);
    SELF_SET(func_800AC754(0));
    Area_SceneSelectRecord(0x1C1);
    Script_Select(8);
    SELF(PartyMember)->unk_2A = 1;
    SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
}
