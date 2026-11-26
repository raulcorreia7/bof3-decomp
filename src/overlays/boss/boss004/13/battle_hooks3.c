#include "boss004_13.h"

#include "overlays/boss/shared/Boss_InstallBattleHooks3.h"

MATCH u8 Boss_RunBattleEvent3(u32 mode) {
    BOSS_RUN_BATTLE_EVENT_BODY(mode);
}

MATCH void Boss_ChooseBattleEnding3(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        g_Game.battle_order = 7;
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

MATCH void Boss_EndBattle3(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        Battle_ShowActorEntry(4);
        Battle_ShowActorEntry(5);
        return;
    }
    Battle_ShowActorEntry(4);
    Battle_CopyActorEntry(4, (PartyMember*)g_BattleEnemyBattlers, 1);
    TASK_SET(func_800AC754(4));
    Area_SceneSelectRecord(0x5F);
    TASK(PartyMember)->unk_48 = 0;
    TASK(PartyMember)->unk_2A = 1;
    Script_Select(1);
    TASK(PartyMember)->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    TASK(PartyMember)->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    Battle_ShowActorEntry(5);
    Battle_CopyActorEntry(5, (PartyMember*)&g_BattleEnemyBattlers[1], 1);
    TASK_SET(func_800AC754(5));
    Area_SceneSelectRecord(0x5F);
    TASK(PartyMember)->unk_48 = 0;
    TASK(PartyMember)->unk_2A = 1;
    Script_Select(1);
    TASK(PartyMember)->unk_58      = g_BattleEnemyBattlers[1].unk_58;
    TASK(PartyMember)->unk_5A      = g_BattleEnemyBattlers[1].unk_5A;
    TASK(PartyMember)->pos.x.fixed = g_BattleEnemyBattlers[1].pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed = g_BattleEnemyBattlers[1].pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed = g_BattleEnemyBattlers[1].pos.z.fixed;
}
