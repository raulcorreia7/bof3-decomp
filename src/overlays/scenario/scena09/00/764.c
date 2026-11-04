#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7364(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FE384[entity[1]]();
}

INCLUDE_ASM(func_801F73A0);

MATCH void func_801F73F0(void) {
    if (!(func_801F75BC() & BYTE_MASK)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F7424);

INCLUDE_ASM(func_801F7574);

INCLUDE_ASM(func_801F75BC);

INCLUDE_ASM(func_801F76D0);

MATCH void func_801F78D0(void) {
    SYS_DISPATCH_BYTE(D_801FE3E0, D_80146872);
}

MATCH void func_801F790C(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7920);

MATCH void func_801F83D8(void) {
    SYS_DISPATCH_BYTE(D_801FE3EC, g_SceneState.state_04);
}

MATCH void func_801F8414(void) {
}

INCLUDE_ASM(func_801F841C);

INCLUDE_ASM(func_801F8504);

INCLUDE_ASM(func_801F8770);

INCLUDE_ASM(func_801F8D30);

INCLUDE_ASM(func_801F9354);

INCLUDE_ASM(func_801F9498);

INCLUDE_ASM(func_801FA08C);

INCLUDE_ASM(func_801FA1F0);

INCLUDE_ASM(func_801FA8B8);

INCLUDE_ASM(func_801FAC88);

INCLUDE_ASM(func_801FAE0C);

INCLUDE_ASM(func_801FBC78);

INCLUDE_ASM(func_801FBD0C);

INCLUDE_ASM(func_801FBD6C);

MATCH void func_801FC588(void) {
}

INCLUDE_ASM(func_801FC590);

MATCH void func_801FC5DC(void) {
}

MATCH void func_801FC5E4(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FE434[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FC624(void) {
}

MATCH void func_801FC62C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FC668(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_SceneState.step_05  = 5;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FC6A4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_SceneState.state_04 = 4;
}

MATCH void func_801FC6DC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xA;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FC710(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xA;
    g_SceneState.step_05  = 1;
}

MATCH void func_801FC748(void) {
    *SP_REF(s8*, 0x44) = 0;
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xD;
    g_SceneState.step_05  = 5;
}

MATCH void func_801FC788(void) {
    SYS_SetFlag(g_SceneFlags, 0xEU);
}

MATCH void func_801FC7B0(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 6;
    g_SceneState.step_05  = 0x64;
}

MATCH void func_801FC7E8(void) {
    SYS_SetFlag(g_SceneFlags, 0x10U);
}

MATCH void func_801FC810(void) {
    SYS_SetFlag(g_SceneFlags, 0x14U);
}

MATCH void func_801FC838(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 8;
    g_SceneState.step_05  = 0xF;
}

MATCH void func_801FC870(void) {
}

MATCH void func_801FC878(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xF;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FC8AC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xF;
    g_SceneState.step_05  = 0x14;
}

MATCH void func_801FC8E4(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xF;
    g_SceneState.step_05  = 0x28;
}

INCLUDE_ASM(func_801FC91C);

MATCH s32 func_801FD278(void) {
    return 0;
}

INCLUDE_ASM(func_801FD280);

/* nonmatching: returns 1 through Game_SetScriptActive delay slots like func_801FDC70; the if/else with one tail is 12 bytes short (first differing instruction: bne at +0x10 targets +0x70 against +0x68): retail repeats li v1,6 in the delay slot of each branch to the shared D_80146874 store. */
INCLUDE_ASM(func_801FD2E8);

INCLUDE_ASM(func_801FD388);

INCLUDE_ASM(func_801FD498);

INCLUDE_ASM(func_801FD5A8);

INCLUDE_ASM(func_801FD6F8);

INCLUDE_ASM(func_801FD7F4);

INCLUDE_ASM(func_801FD8F0);

INCLUDE_ASM(func_801FD978);

INCLUDE_ASM(func_801FDA04);

INCLUDE_ASM(func_801FDA90);

INCLUDE_ASM(func_801FDB1C);

INCLUDE_ASM(func_801FDBA8);

INCLUDE_ASM(func_801FDC1C);

/* Returns -1 when scene flag 0x33 is set; else sets the script active, D_80146875 = 0x32 (0x34 unless D_80145F09 == 4),
 * D_80146874 = 0xF and returns 1. The early-return shape is 4 bytes short: retail puts li v0,1 in the delay slot of each
 * Game_SetScriptActive call (first differing instruction: bnez at +0x18 targets +0x74 against +0x70). Same signature as
 * scena01 func_801FE0A4. */
INCLUDE_ASM(func_801FDC70);

MATCH void func_801FDCF4(void) {
    EMI_LoaderStreamFamily(7U, 8U, 2U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(8);
    func_801C1630();
}

MATCH void func_801FDD38(void) {
    EMI_LoaderStreamFamily(7U, 8U, 2U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(2);
    func_801C1630();
}

MATCH void func_801FDD7C(void) {
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_JoinMember(CHAR_ID_MOMO);
    func_801C1630();
}

#include "overlays/scenario/Scene_JoinMomo.h"

#include "overlays/scenario/Scene_JoinAdultNina.h"

MATCH void func_801FDE50(void) {
    Party_BuildBattlers(0);
    Party_JoinMember(6);
    func_801C1630();
}

MATCH void func_801FDE80(void) {
    EMI_LoaderStreamFamily(7U, 6U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_JoinMember(CHAR_ID_PECO);
    func_801C1630();
}

#include "overlays/scenario/Scene_JoinPeco.h"

MATCH void func_801FDF10(void) {
    EMI_LoaderStreamFamily(7U, 6U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(5);
    func_801C1630();
}

#include "overlays/scenario/Scene_RebuildRyuGarrParty.h"

MATCH void func_801FE014(void) {
    EMI_LoaderStreamFamily(7U, 4U, 8U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(8);
    func_801C1630();
}

MATCH void func_801FE058(void) {
    EMI_LoaderStreamFamily(7, 4, 8, 0);
    Party_BuildBattlers(0);
    Party_JoinMember(4);
    Party_JoinMember(8);
    func_801C1630();
}

MATCH void func_801FE0A4(void) {
    EMI_LoaderStreamFamily(7U, 4U, 8U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(4);
    func_801C1630();
}

MATCH void func_801FE0E8(void) {
    EMI_LoaderStreamFamily(7U, 4U, 8U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(7);
    func_801C1630();
}

#include "overlays/scenario/Scene_RemoveRei.h"

MATCH void func_801FE154(void) {
    func_801C1ABC(4);
    func_801C1ABC(2);
    func_801C1630();
}

#include "overlays/scenario/Scene_RemoveGarr.h"

MATCH void func_801FE1AC(void) {
    func_801C1ABC(2);
    func_801C1ABC(8);
    func_801C1630();
}

MATCH void func_801FE1DC(void) {
    func_801C1ABC(4);
    func_801C1ABC(8);
    func_801C1630();
}

#include "overlays/scenario/Scene_RemoveAdultNina.h"

#include "overlays/scenario/Scene_StashPartyExceptRyuAdult.h"

#include "overlays/scenario/Scene_RemoveMomo.h"

#include "overlays/scenario/Scene_RemovePeco.h"

MATCH void func_801FE35C(void) {
    func_801C1ABC(7);
    func_801C1630();
}
