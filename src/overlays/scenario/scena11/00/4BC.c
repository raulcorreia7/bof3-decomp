#include "scena11_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F70BC(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FAEC0[entity[1]]();
    g_AreaViewRefreshCount = 2;
}

INCLUDE_ASM(func_801F7104);

INCLUDE_ASM(func_801F7178);

INCLUDE_ASM(func_801F7200);

MATCH void func_801F7288(void) {
    SYS_DISPATCH_BYTE(D_801FAEF0, D_80146872);
}

MATCH void func_801F72C4(void) {
    g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    D_80146872      = 1;
}

INCLUDE_ASM(func_801F72E4);

MATCH void func_801F7748(void) {
    SYS_DISPATCH_BYTE(D_801FAEFC, g_SceneState.state_04);
}

MATCH void func_801F7784(void) {
}

INCLUDE_ASM(func_801F778C);

INCLUDE_ASM(func_801F7BFC);

INCLUDE_ASM(func_801F7CC8);

INCLUDE_ASM(func_801F7F08);

INCLUDE_ASM(func_801F82D8);

INCLUDE_ASM(func_801F83C8);

/* Stores GAME_REQUEST_STATUS_MENU to g_GameStateIndex (at 0x801F8D2C). */
INCLUDE_ASM(func_801F8B84);

MATCH void func_801F917C(void) {
}

INCLUDE_ASM(func_801F9184);

INCLUDE_ASM(func_801FA3A4);

MATCH void func_801FA5B8(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FAF24[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FA5F8(void) {
}

INCLUDE_ASM(func_801FA600);

MATCH void func_801FA674(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 3;
}

MATCH void func_801FA6C0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FA70C(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0xa;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 3;
}

MATCH void func_801FA75C(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 6;
}

MATCH void func_801FA7A8(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 7;
}

MATCH void func_801FA7F4(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 9;
}

MATCH void func_801FA840(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 9;
}

MATCH void func_801FA890(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x14;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 0xa;
}

MATCH void func_801FA8E0(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x14;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 0xb;
}

MATCH void func_801FA930(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 11;
}

MATCH void func_801FA988(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 14;
}

MATCH void func_801FA9D4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x1e;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 0xe;
}

MATCH void func_801FAA24(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x28;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 5;
}

INCLUDE_ASM(func_801FAA74);

MATCH s32 func_801FAB64(void) {
    return 0;
}

MATCH s32 func_801FAB6C(void) {
    return -1;
}

INCLUDE_ASM(func_801FAB74);

MATCH void func_801FABC0(void) {
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(8);
    func_801C1630();
}

MATCH void func_801FAC04(void) {
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(5);
    func_801C1630();
}

INCLUDE_ASM(func_801FAC48);

MATCH void func_801FAC94(void) {
    EMI_LoaderStreamFamily(7U, 2U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(5);
    func_801C1630();
}

MATCH void func_801FACD8(void) {
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(5);
    func_801C1630();
}

INCLUDE_ASM(func_801FAD1C);

MATCH void func_801FAD68(void) {
    EMI_LoaderStreamFamily(7U, 6U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(6);
    func_801C1630();
}

MATCH void func_801FADAC(void) {
    EMI_LoaderStreamFamily(7, 4, 2, 0);
    func_801C1400(0);
    func_801C187C(4);
    func_801C187C(2);
    func_801C1630();
}

#include "overlays/scenario/Scene_RemoveRei.h"

MATCH void func_801FAE20(void) {
    func_801C1ABC(2);
    func_801C1630();
}

#include "overlays/scenario/Scene_RemovePeco.h"

#include "overlays/scenario/Scene_RemoveMomo.h"

MATCH void func_801FAE98(void) {
    func_801C1ABC(8);
    func_801C1630();
}
