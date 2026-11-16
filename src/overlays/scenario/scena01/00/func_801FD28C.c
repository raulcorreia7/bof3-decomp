#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/Area_DrawDimQuad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Give the lead party member a field actor of type 6: claim a free slot and seed its row from the member. */
MATCH void func_801FD28C(s32 variant){ACTOR_SEED_PARTY_SLOT(0, D_801FE280, 6, variant + 112)}

MATCH void func_801FD444(void* record) {
    D_801FE308[((Actor*)record)->callback_index](record, &D_80144E90);
}

MATCH void func_801FD484(void) {
}

MATCH void func_801FD48C(void) {
    if (SYS_TestFlag(g_SceneFlags, 20) == 0) {
        *g_ScriptVars = 0;
        Game_SetScriptActive();
        D_80146875 = 0;
        D_80146874 = 0x12;
        SYS_SetFlag(g_SceneFlags, 20U);
    }
}

MATCH void func_801FD4F0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 23;
}

MATCH void func_801FD534(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 23;
}

MATCH void func_801FD57C(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 23;
}

MATCH void func_801FD5C4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 17;
}

MATCH void func_801FD60C(Actor* actor) {
    Game_SetScriptActive();
    g_ScriptVars[0]      = 10;
    g_ScriptVars[1]      = 0;
    g_ScriptVars[2]      = 0;
    actor->header.mode   = 4;
    actor->unk_7E        = 0;
    actor->unk_7B        = 0;
    actor->unk_77        = 10;
    g_Task->direction_08 = g_Game.members[0].facing ^ 4;
    func_8015BAC4(g_Task->direction_08);
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_SceneState.step_05  = 10;
    g_SceneState.state_04 = 13;
}

MATCH void func_801FD6CC(Actor* actor) {
    Game_SetScriptActive();
    actor->header.mode   = 4;
    actor->unk_7B        = 0;
    actor->unk_77        = 0xA;
    g_Task->direction_08 = g_Game.members[0].facing ^ 0x4;
    func_8015BAC4(g_Task->direction_08);
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 13;
    g_SceneState.state_04 = 13;
}

MATCH void func_801FD788(Actor* actor) {
    Game_SetScriptActive();
    actor->header.mode   = 4;
    actor->unk_7E        = 0;
    actor->unk_7B        = 0;
    actor->unk_77        = 11;
    g_Task->direction_08 = g_Game.members[0].facing ^ 4;
    func_8015BAC4(g_Task->direction_08);
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_SceneState.step_05  = 16;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 13;
}

MATCH void func_801FD84C(Actor* actor) {
    Game_SetScriptActive();
    actor->header.mode   = 4;
    actor->unk_7E        = 0;
    actor->unk_7B        = 0;
    actor->unk_77        = 0xB;
    g_Task->direction_08 = g_Game.members[0].facing ^ 0x4;
    func_8015BAC4(g_Task->direction_08);
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_SceneState.step_05  = 16;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 13;
}

MATCH void func_801FD8F8(void) {
    g_ScriptVars[0] = 0x64;
}

MATCH void func_801FD90C(void) {
    g_ScriptVars[0] = 0x66;
}

MATCH void func_801FD920(void) {
    g_ScriptVars[0] = 0x67;
}

MATCH void func_801FD934(void) {
    g_ScriptVars[0] = 0x68;
}

MATCH void func_801FD948(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 40;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 9;
}

MATCH void func_801FD9A0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 17;
}

MATCH void func_801FD9E4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 17;
}

MATCH void func_801FDA2C(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0xF;
    g_SceneState.state_04 = 0xB;
}

MATCH s32 func_801FDA64(void) {
    return 0;
}

INCLUDE_ASM(func_801FDA6C);

MATCH s8 func_801FE03C(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FE350, 2, D_801FE35C);
}

MATCH s32 func_801FE0A4(void) {
    if (SYS_TestFlag(g_SceneFlags, 3) == 0 || SYS_TestFlag(g_SceneFlags, 4)) {
        return -1;
    }

    Game_SetScriptActive();
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 5;
    return 1;
}

/* func_801FE10C */
MATCH void Scene_InitOpeningParty(void) {
    g_Characters[g_CharSlot[10]].party_flags &= ~PARTY_FLAG_JOINED;
    EMI_LoadPartyArchives(CHAR_ID_RYU_PAJAMAS, CHAR_ID_TEEPO, CHAR_ID_REI, 0);
    g_Game.party_size                        = 0;
    g_Characters[g_CharSlot[9]].character_id = CHAR_ID_RYU_PAJAMAS;
    Party_JoinMember(CHAR_ID_RYU_PAJAMAS);
}

/* func_801FE1B0 */
MATCH void Scene_SetPartyRyuTeepoRei(void) {
    g_Characters[g_CharSlot[0]].character_id = CHAR_ID_RYU_YOUNG;
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_TEEPO, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
    Party_JoinMember(CHAR_ID_TEEPO);
    Party_JoinMember(CHAR_ID_REI);
}

/* func_801FE224 */
MATCH void Party_JoinRei(void) {
    Party_JoinMember(CHAR_ID_REI);
}

#include "overlays/scenario/Scene_RemoveRei.h"
