#include "boss004_13.h"

#include "overlays/boss/shared/Boss_InstallBattleHooks2.h"

MATCH u8 Boss_RunBattleEvent2(u32 mode) {
    BOSS_RUN_BATTLE_EVENT_BODY(mode);
}

MATCH void Boss_ChooseBattleEnding2(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        g_Game.battle_order = 8;
        g_Battle.outcome.options |= 0x80;
        Battle_EndToArea();
        g_ScenarioState.step = 0x32;
    } else {
        u8* step;

        step = &g_ScenarioState.step;
        (*step)++;
        Battle_EndToArea();
    }
}

MATCH void Boss_EndBattle2(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        Battle_ShowActorEntry(2);
        Battle_ShowActorEntry(3);
        return;
    }
    Battle_ShowActorEntry(2);
    Battle_CopyActorEntry(2, (PartyMember*)g_BattleEnemyBattlers, 1);
    SELF_SET(func_800AC754(2));
    Area_SceneSelectRecord(0x5F);
    SELF(PartyMember)->unk_48 = 0;
    SELF(PartyMember)->unk_2A = 0;
    Script_Select(1);
    SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    Battle_ShowActorEntry(3);
    Battle_CopyActorEntry(3, (PartyMember*)&g_BattleEnemyBattlers[1], 1);
    SELF_SET(func_800AC754(3));
    Area_SceneSelectRecord(0x5F);
    SELF(PartyMember)->unk_48 = 0;
    SELF(PartyMember)->unk_2A = 0;
    Script_Select(1);
    SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[1].unk_58;
    SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[1].unk_5A;
}
