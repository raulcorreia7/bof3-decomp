#include "scena01_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801F71C0);

INCLUDE_ASM(func_801F729C);

MATCH void func_801F73B8(void) {
    SYS_DISPATCH_TASK(D_801FE26C, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F73FC);

MATCH void func_801F7480(void) {
    func_801F7678(g_SpadWork->unk_09);
    if ((g_FrameCount & 1) == 0) {
        func_801F7AE4();
    }
    func_801F7C54();
    g_SpadWork->unk_09 = ((Actor*)g_SpadWork)->unk_09 + 4;
    if (g_SpadWork->unk_09 == 0) {
        g_SpadWork->unk_09 = 0x20;
        g_SpadWork->unk_01 = ((Actor*)g_SpadWork)->unk_01 + 1;
    }
}

INCLUDE_ASM(func_801F752C);

MATCH void func_801F75C8(void) {
    func_801F7678(g_SpadWork->unk_09);
    func_801F7C54();
    g_SpadWork->unk_09 = ((Actor*)g_SpadWork)->unk_09 - 4;
    if (g_SpadWork->unk_09 == 0) {
        g_SpadWork->unk_01 = ((Actor*)g_SpadWork)->unk_01 + 1;
    }
}

MATCH void func_801F7644(void) {
    if (!(func_801F7C54() & BYTE_MASK)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F7678);

INCLUDE_ASM(func_801F7A24);

#include "shared/Area_ClearWorkColumn.h"

INCLUDE_ASM(func_801F7AE4);

INCLUDE_ASM(func_801F7C54);

INCLUDE_ASM(func_801F7D04);

INCLUDE_ASM(func_801F7DCC);

INCLUDE_ASM(func_801F7EDC);

MATCH void func_801F7FC4(void) {
    SYS_DISPATCH_BYTE(D_801FE29C, D_80146872);
}

INCLUDE_ASM(func_801F8000);

INCLUDE_ASM(func_801F8050);

MATCH void func_801F8AA0(void) {
    SYS_DISPATCH_BYTE(D_801FE2A8, g_SceneState.state_04);
}

MATCH void func_801F8ADC(void) {
}

INCLUDE_ASM(func_801F8AE4);

INCLUDE_ASM(func_801F8C0C);

INCLUDE_ASM(func_801F8F34);

MATCH void func_801F986C(void) {
}

INCLUDE_ASM(func_801F9874);

INCLUDE_ASM(func_801F9AA0);

MATCH void func_801FA244(void) {
}

INCLUDE_ASM(func_801FA24C);

INCLUDE_ASM(func_801FA844);

INCLUDE_ASM(func_801FB218);

INCLUDE_ASM(func_801FB5BC);

INCLUDE_ASM(func_801FBB1C);

INCLUDE_ASM(func_801FBF30);

INCLUDE_ASM(func_801FC488);

INCLUDE_ASM(func_801FC6B4);

MATCH void func_801FC890(void) {
}

INCLUDE_ASM(func_801FC898);

INCLUDE_ASM(func_801FCC24);

MATCH void func_801FCCF4(void) {
}

MATCH void func_801FCCFC(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(0x18);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                D_80146865 = 0;
                D_80146866 = 0;
                *state     = 0;
                D_80146874 = 0;
            }
            return;
    }
}

MATCH void func_801FCD9C(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(0x34);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state     = 0;
                D_80146874 = 0x6;
            }
            return;
    }
}

MATCH void func_801FCE30(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(0x34);
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

INCLUDE_ASM(func_801FCEC0);

INCLUDE_ASM(func_801FD28C);

MATCH void func_801FD444(void* record) {
    D_801FE308[((Actor*)record)->callback_index](record, &D_80144E90);
}

MATCH void func_801FD484(void) {
}

MATCH void func_801FD48C(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x14) == 0) {
        *g_ScriptVars = 0;
        Game_SetScriptActive();
        D_80146875 = 0;
        D_80146874 = 0x12;
        SYS_SetFlag(g_SceneFlags, 0x14U);
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

INCLUDE_ASM(func_801FD60C);

INCLUDE_ASM(func_801FD6CC);

INCLUDE_ASM(func_801FD788);

INCLUDE_ASM(func_801FD84C);

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

INCLUDE_ASM(func_801FE03C);

/* Returns -1 unless scene flag 3 is set and flag 4 clear, else sets the script active, D_80146874 = 5 and returns 1.
 * Three shapes (early returns, nested ifs, one result local) fail: retail loads the return 1 into the delay slot of
 * Game_SetScriptActive, the C puts li v1,5 there (first differing instruction, +0x40: li v0,1). */
INCLUDE_ASM(func_801FE0A4);

MATCH void func_801FE10C(void) {
    g_Characters[g_CharSlot[10]].unk_07 &= 0xFE;
    EMI_LoaderStreamFamily(9, 3, 4, 0);
    g_PartySize                              = 0;
    g_Characters[g_CharSlot[9]].character_id = 9;
    Party_JoinMember(9);
}

MATCH void func_801FE1B0(void) {
    g_Characters[g_CharSlot[0]].character_id = 0;
    EMI_LoaderStreamFamily(0, 3, 4, 0);
    g_PartySize = 0;
    Party_JoinMember(0);
    Party_JoinMember(3);
    Party_JoinMember(4);
}

MATCH void func_801FE224(void) {
    Party_JoinMember(4);
}

#include "overlays/scenario/Scene_RemoveRei.h"
