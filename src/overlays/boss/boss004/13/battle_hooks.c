#include "boss004_13.h"

MATCH void func_800C1860(void) {
    SYS_DISPATCH_TASK(D_800C2740, 1, g_Self);
}

MATCH void func_800C18A4(void) {
    Boss_StartEnemyScript(D_800C2720, func_800C1BBC, D_800C2738);
}

MATCH void func_800C18FC(void) {
    SYS_DISPATCH_TASK(D_800C2770, 2, g_Self);
}

MATCH void Boss_EndDefeat(void) {
    BOSS_FINISH_DEFEAT();
}

MATCH void func_800C19C0(void) {
    SYS_DISPATCH_TASK(D_800C2788, 2, g_Self);
}

MATCH void func_800C1A04(void) {
    Battle_RequestEnemyScript(4);
    SELF(PartyMember)->unk_09 = 60;
    SELF(PartyMember)->header.step++;
}

MATCH void func_800C1A4C(void) {
    u8* result;
    u8  timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        Area_SceneSelectRecord(0x5F);
        if (g_Battle.encounter == 5) {
            SELF(PartyMember)->unk_2A = 0;
            SELF(PartyMember)->pos.y.fixed += TO_COORD(1) + COORD_HALF;
        } else {
            SELF(PartyMember)->unk_2A = 1;
            SELF(PartyMember)->pos.x.fixed += TO_COORD(1) + COORD_HALF;
        }
        COORD_INT(SELF(PartyMember)->pos.z) = Area_HeightSample(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed);
        g_BattleCurrentEnemy->script        = &D_800C272C;
        Script_Select(1U);
        result = &g_Battle.outcome.result;
        *result |= 4;
        g_Battle.boss_flags |= 1 << SELF(PartyMember)->slot;
        SELF(PartyMember)->header.step += 1;
    }
    Script_AnimStepLoop();
}

MATCH void func_800C1B9C(void) {
    Script_AnimStepLoop();
}

MATCH void func_800C1BBC(s32 mode) {
    D_800C2794[(u8)mode]();
}

MATCH void func_800C1BF4(void) {
}

MATCH void func_800C1BFC(void) {
}

MATCH void func_800C1C04(void) {
}

#include "overlays/boss/shared/Boss_InstallBattleHooks.h"

MATCH u8 Boss_RunBattleEvent(u32 mode) {
    BOSS_RUN_BATTLE_EVENT_BODY(mode);
}

MATCH void Boss_ChooseBattleEnding(void) {
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
