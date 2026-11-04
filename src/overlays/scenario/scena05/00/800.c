#include "scena05_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7400(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FD5A8[entity[1]]();
}

MATCH void func_801F743C(void) {
    void* temp_v1_5;

    temp_v1_5                   = SP_REF(void*, 0x44);
    FIELD(s32, temp_v1_5, 0xCu) = 0;
    FIELD(u8, temp_v1_5, 0x1u)  = (u8)(FIELD(u8, temp_v1_5, 0x1u) + 1);
}

INCLUDE_ASM(func_801F745C);

MATCH void func_801F74CC(void) {
    Actor_Clear();
}

MATCH void func_801F74EC(void) {
    SYS_DISPATCH_TASK(D_801FD5B4, 1, g_SpadWork);
}

MATCH void func_801F7530(void) {
    void* temp_v0_5;

    temp_v0_5                   = SP_REF(void*, 0x44);
    FIELD(s32, temp_v0_5, 0xCu) = 0x1000;
    FIELD(u8, temp_v0_5, 0x1u)  = (u8)(FIELD(u8, temp_v0_5, 0x1u) + 1);
}

INCLUDE_ASM(func_801F7554);

MATCH void func_801F7640(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F7660);

MATCH void func_801F7A78(void) {
    SYS_DISPATCH_BYTE(D_801FD5DC, D_80146872);
}

MATCH void func_801F7AB4(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7AC8);

MATCH void func_801F83EC(void) {
    SYS_DISPATCH_BYTE(D_801FD5E8, g_SceneState.state_04);
}

MATCH void func_801F8428(void) {
}

INCLUDE_ASM(func_801F8430);

MATCH void func_801F8554(void) {
}

MATCH void func_801F855C(void) {
}

INCLUDE_ASM(func_801F8564);

INCLUDE_ASM(func_801F87C4);

INCLUDE_ASM(func_801F8B94);

MATCH void func_801F8C1C(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(0x26);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state     = 0;
                D_80146874 = 0;
            }
            return;
    }
}

INCLUDE_ASM(func_801F8CAC);

INCLUDE_ASM(func_801F8EB0);

INCLUDE_ASM(func_801F9148);

MATCH void func_801F92EC(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(0);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state     = 0;
                D_80146874 = 0;
            }
            return;
    }
}

MATCH void func_801F937C(void) {
}

INCLUDE_ASM(func_801F9384);

INCLUDE_ASM(func_801F96E0);

MATCH void func_801F989C(void) {
}

INCLUDE_ASM(func_801F98A4);

INCLUDE_ASM(func_801FB66C);

INCLUDE_ASM(func_801FBDBC);

MATCH void func_801FC2F0(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(0x84);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state     = 0;
                D_80146874 = 0;
            }
            return;
    }
}

INCLUDE_ASM(func_801FC380);

INCLUDE_ASM(func_801FC6A8);

MATCH void func_801FC778(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(0x4C);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state     = 0;
                D_80146874 = 0;
            }
            return;
    }
}

INCLUDE_ASM(func_801FC808);

INCLUDE_ASM(func_801FC8A0);

MATCH void func_801FCA58(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FD644[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FCA98(void) {
}

INCLUDE_ASM(func_801FCAA0);

MATCH void func_801FCB1C(void) {
    SYS_SetFlag(g_SceneFlags, 11);
    Game_SetScriptActive();
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146875      = 0;
    D_80146874      = 8;
}

MATCH void func_801FCB80(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 12;
}

MATCH void func_801FCBD4(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 13;
}

MATCH void func_801FCC28(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 16;
}

MATCH void func_801FCC74(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 17;
}

MATCH void func_801FCCC0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 18;
}

MATCH void func_801FCD0C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 13;
}

MATCH s32 func_801FCD60(void) {
    return 0;
}

INCLUDE_ASM(func_801FCD68);

INCLUDE_ASM(func_801FD110);

INCLUDE_ASM(func_801FD178);

INCLUDE_ASM(func_801FD208);

MATCH void func_801FD298(void) {
    g_Characters[g_CharSlot[6]].unk_07 |= 1;
    Party_BuildBattlers(0);
    Party_JoinMember(5);
    Party_JoinMember(1);
    Party_JoinMember(6);
}

MATCH void func_801FD30C(void) {
    Party_JoinMember(1);
}

MATCH void func_801FD32C(void) {
    Party_JoinMember(5);
}

MATCH void func_801FD34C(void) {
    Party_JoinMember(6);
}

MATCH void func_801FD36C(void) {
    Party_JoinMember(0);
}

MATCH void func_801FD38C(void) {
    EMI_LoaderStreamFamily(0U, 1U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(5);
}

MATCH void func_801FD3C8(void) {
    EMI_LoaderStreamFamily(0U, 1U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(1);
}

MATCH void func_801FD404(void) {
    EMI_LoaderStreamFamily(0U, 1U, 6U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(6);
}

MATCH void func_801FD440(void) {
    Party_JoinMember(2);
}

MATCH void func_801FD460(void) {
    EMI_LoaderStreamFamily(0U, 1U, 2U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(1);
}

MATCH void func_801FD49C(void) {
    EMI_LoaderStreamFamily(0U, 1U, 2U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(1);
}

MATCH void func_801FD4D8(void) {
    func_801C1ABC(5);
    func_801C1ABC(1);
    func_801C1630();
}

MATCH void func_801FD508(void) {
    func_801C1ABC(1);
    func_801C1630();
}

MATCH void func_801FD530(void) {
    func_801C1ABC(5);
    func_801C1630();
}

MATCH void func_801FD558(void) {
    func_801C1ABC(6);
    func_801C1630();
}

MATCH void func_801FD580(void) {
    func_801C1ABC(0);
    func_801C1630();
}
