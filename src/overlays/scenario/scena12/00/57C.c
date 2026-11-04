#include "scena12_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F717C(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FD178[entity[1]]();
}

MATCH void func_801F71B8(void) {
    SYS_DISPATCH_TASK(D_801FD184, 2, g_SpadWork);
}

INCLUDE_ASM(func_801F71FC);

INCLUDE_ASM(func_801F7240);

/* The statements of func_801F7348 and func_801F7518, byte-identical twins: unless a message is pending, the entry state
 * is 4 or scene flag 0x2E is set, queue script step 5 with D_80146875 = 0x19, raise the script-active flag and clear
 * the work. Every change here must verify both members. */
#define SCENA12_START_SCRIPT()                                                                                        \
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_GameEntryState != 4 && SYS_TestFlag(g_SceneFlags, 0x2E) == 0) { \
        D_80146875 = 0x19;                                                                                            \
        D_80146874 = 5;                                                                                               \
        g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;                                                                       \
        Actor_Clear();                                                                                                \
    }

MATCH void func_801F7348(void) {
    SCENA12_START_SCRIPT();
}

MATCH void func_801F73CC(void) {
    SYS_DISPATCH_TASK(D_801FD190, 2, g_SpadWork);
}

INCLUDE_ASM(func_801F7410);

MATCH void func_801F7518(void) {
    SCENA12_START_SCRIPT();
}

INCLUDE_ASM(func_801F759C);

INCLUDE_ASM(func_801F75EC);

INCLUDE_ASM(Menu_DrawHeaderBar);

MATCH void func_801F7BA8(void) {
    SYS_DISPATCH_TASK(D_801FD198, 1, g_SpadWork);
}

MATCH void func_801F7BEC(void) {
    Actor* actor;

    actor         = g_SpadWork;
    actor->unk_2E = 0;
    actor->unk_01 = actor->unk_01 + 1;
    SND_PlayCue(EMI_CUE_ID(2, 21));
}

INCLUDE_ASM(func_801F7C24);

MATCH void func_801F7E14(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F7E34);

MATCH void func_801F7F28(void) {
    SYS_DISPATCH_BYTE(D_801FD1B8, D_80146872);
}

MATCH void func_801F7F64(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7F78);

MATCH void func_801F886C(void) {
    SYS_DISPATCH_BYTE(D_801FD1C4, g_SceneState.state_04);
}

MATCH void func_801F88A8(void) {
}

INCLUDE_ASM(func_801F88B0);

INCLUDE_ASM(func_801F894C);

MATCH void func_801F89FC(void) {
}

INCLUDE_ASM(func_801F8A04);

INCLUDE_ASM(func_801F9680);

INCLUDE_ASM(func_801F9F0C);

INCLUDE_ASM(func_801FA7DC);

INCLUDE_ASM(func_801FAE04);

INCLUDE_ASM(func_801FB864);

MATCH void func_801FC574(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FD1EC[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FC5B4(void) {
}

MATCH void func_801FC5BC(void) {
}

MATCH void func_801FC5C4(void) {
}

MATCH void func_801FC5CC(void) {
}

MATCH void func_801FC5D4(void) {
}

MATCH void func_801FC5DC(void) {
}

MATCH void func_801FC5E4(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 1;
}

MATCH void func_801FC630(void) {
}

MATCH void func_801FC638(void) {
}

MATCH void func_801FC640(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x14;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 4;
}

MATCH void func_801FC690(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x14;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FC6E0(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FC738(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 8;
}

MATCH void func_801FC784(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x1e;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 8;
}

MATCH void func_801FC7D4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0xA;
    g_SceneState.state_04 = 1;
}

INCLUDE_ASM(func_801FC80C);

INCLUDE_ASM(func_801FC890);

INCLUDE_ASM(func_801FCC54);

INCLUDE_ASM(func_801FCCBC);

MATCH s32 func_801FCD38(void) {
    SND_PlayCue(EMI_CUE_ID(2, 9));
    return -1;
}

INCLUDE_ASM(func_801FCD58);

INCLUDE_ASM(func_801FCDE0);

MATCH void func_801FCE2C(void) {
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(8);
    func_801C1630();
}

MATCH void func_801FCE70(void) {
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(5);
    func_801C1630();
}

INCLUDE_ASM(func_801FCEB4);

MATCH void func_801FCF00(void) {
    EMI_LoaderStreamFamily(7U, 2U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(5);
    func_801C1630();
}

MATCH void func_801FCF44(void) {
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(5);
    func_801C1630();
}

INCLUDE_ASM(func_801FCF88);

MATCH void func_801FCFD4(void) {
    EMI_LoaderStreamFamily(7U, 6U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(6);
    func_801C1630();
}

MATCH void func_801FD018(void) {
    EMI_LoaderStreamFamily(7, 4, 2, 0);
    func_801C1400(0);
    func_801C187C(4);
    func_801C187C(2);
    func_801C1630();
}

MATCH void func_801FD064(void) {
    EMI_LoaderStreamFamily(7, 5, 2, 0);
    Party_BuildBattlers(0);
    Party_JoinMember(2);
    Party_JoinMember(5);
    func_801C1630();
}

MATCH void func_801FD0B0(void) {
    func_801C1ABC(4);
    func_801C1630();
}

MATCH void func_801FD0D8(void) {
    func_801C1ABC(2);
    func_801C1630();
}

MATCH void func_801FD100(void) {
    func_801C1ABC(6);
    func_801C1630();
}

#include "overlays/scenario/Scene_RemoveMomo.h"

MATCH void func_801FD150(void) {
    func_801C1ABC(8);
    func_801C1630();
}
