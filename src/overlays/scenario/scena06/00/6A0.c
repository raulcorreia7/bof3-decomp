#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F72A0(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    ORDER_LOCK(D_801FE3D8[index]());
}

MATCH void func_801F72D4(void) {
    func_801FD29C();
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7300);

MATCH void func_801F7A00(void) {
    SYS_DISPATCH_BYTE(D_801FE3E4, g_SceneState.state_04);
}

MATCH void func_801F7A3C(void) {
}

INCLUDE_ASM(func_801F7A44);

INCLUDE_ASM(func_801F7C6C);

INCLUDE_ASM(func_801F8188);

INCLUDE_ASM(func_801F8B50);

INCLUDE_ASM(func_801F8F18);

INCLUDE_ASM(func_801F90C0);

/* Stores GAME_REQUEST_ABILITY_MENU to g_GameStateIndex twice (at 0x801F98D8 and 0x801F9ADC). */
INCLUDE_ASM(func_801F97C0);

/* Stores GAME_REQUEST_ABILITY_MENU to g_GameStateIndex (at 0x801FA1AC). */
INCLUDE_ASM(func_801F9DF4);

INCLUDE_ASM(func_801FA3D0);

INCLUDE_ASM(func_801FA760);

INCLUDE_ASM(func_801FA8EC);

INCLUDE_ASM(func_801FAB08);

INCLUDE_ASM(func_801FB014);

INCLUDE_ASM(func_801FB30C);

INCLUDE_ASM(func_801FBC88);

INCLUDE_ASM(func_801FBD88);

INCLUDE_ASM(func_801FC498);

INCLUDE_ASM(func_801FC718);

INCLUDE_ASM(func_801FCB80);

INCLUDE_ASM(func_801FCD38);

MATCH void func_801FCDD0(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FE42C[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FCE10(void) {
}

MATCH void func_801FCE18(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 1;
}

MATCH void func_801FCE6C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 2;
}

MATCH void func_801FCEC0(void) {
    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
        Game_SetScriptActive();
        D_80146875    = 0xA;
        *g_ScriptVars = 0;
        D_80146865    = 0;
        D_80146866    = 0;
        D_80146867    = 0;
        D_80146874    = 2;
    }
}

MATCH void func_801FCF30(void) {
    Game_SetScriptActive();
    D_80146875      = 15;
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146874      = 2;
    SYS_SetFlag(g_SceneFlags, 4);
}

MATCH void func_801FCF98(void) {
    SYS_SetFlag(g_SceneFlags, 0xCU);
}

MATCH void func_801FCFC0(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 4;
}

MATCH void func_801FD014(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 20;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 4;
}

MATCH void func_801FD06C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 1;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 6;
}

MATCH void func_801FD0C4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 20;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 6;
}

MATCH void func_801FD11C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 10;
}

MATCH void func_801FD170(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 10;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 14;
}

MATCH void func_801FD1C8(void) {
    Game_SetScriptActive();
    *g_ScriptVars = 0;
    D_80146865    = 0;
    if (SYS_TestFlag(g_SceneFlags, 0x22) == 0) {
        D_80146875 = 0;
    } else {
        D_80146875 = 0x14;
    }
    D_80146874 = 0x10;
}

INCLUDE_ASM(func_801FD234);

MATCH s32 func_801FD294(void) {
    return 0;
}

MATCH void func_801FD29C(void) {
    D_80144DF8 = D_801FE464;
    D_80144DF2 = D_801FE46A;
    D_80144DF5 = D_801FE46B;
    D_80144E00 = D_801FE465;
    D_80144E20 = D_801FE465;
    D_80144E04 = D_801FE466;
    D_80144E24 = D_801FE466;
    D_80144E06 = D_801FE467;
    D_80144E26 = D_801FE467;
    D_80144E08 = D_801FE468;
    D_80144E28 = D_801FE468;
    D_80144E0A = D_801FE469;
    D_80144E2A = D_801FE469;
}

MATCH s8 func_801FD34C(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_step, u8 landing_script, u8 flags) {
    return D_801FE46C[((Actor*)g_SpadWork)->unk_04](entry, dir_x, dir_y, vz_start, vz_step, landing_script, flags);
}

INCLUDE_ASM(func_801FD3BC);

INCLUDE_ASM(func_801FD568);

INCLUDE_ASM(func_801FD748);

INCLUDE_ASM(func_801FD800);

INCLUDE_ASM(func_801FDD14);

INCLUDE_ASM(func_801FDD7C);

MATCH void func_801FDE2C(void) {
}

INCLUDE_ASM(func_801FDE34);

INCLUDE_ASM(func_801FDEA4);

MATCH void func_801FDFFC(void) {
    EMI_LoaderStreamFamily(0U, 1U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(0);
    Party_JoinMember(5);
    func_801C1630();
}

MATCH void func_801FE048(void) {
    EMI_LoaderStreamFamily(0U, 1U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(5);
    func_801C1630();
}

MATCH void func_801FE08C(void) {
    EMI_LoaderStreamFamily(0U, 1U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(1);
    func_801C1630();
}

MATCH void func_801FE0D0(void) {
    EMI_LoaderStreamFamily(0U, 1U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(1);
    Party_JoinMember(5);
    func_801C1630();
}

MATCH void func_801FE11C(void) {
    Party_JoinMember(5);
}

MATCH void func_801FE13C(void) {
    Party_JoinMember(6);
}

#include "overlays/scenario/Scene_JoinNina.h"

MATCH void func_801FE198(void) {
    EMI_LoaderStreamFamily(0U, 1U, 2U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(2);
}

MATCH void Scene_JoinNina_801FE1D4(void) {
    SCENE_JOIN_NINA();
}

MATCH void func_801FE210(void) {
    EMI_LoaderStreamFamily(0U, 1U, 2U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(1);
    Party_JoinMember(2);
}

MATCH void func_801FE254(void) {
    func_801C1ABC(0);
    func_801C1ABC(2);
    func_801C1630();
}

MATCH void func_801FE284(void) {
    func_801C1ABC(0);
    func_801C1ABC(5);
    func_801C1630();
}

MATCH void func_801FE2B4(void) {
    func_801C1ABC(0);
    func_801C1ABC(6);
    func_801C1630();
}

#include "overlays/scenario/Scene_RemoveGarr.h"

#include "overlays/scenario/Scene_RemovePeco.h"

MATCH void func_801FE334(void) {
    func_801C1ABC(6);
    func_801C1ABC(2);
    func_801C1630();
}

#include "overlays/scenario/Scene_RemoveMomo.h"

MATCH void func_801FE38C(void) {
    func_801C1ABC(5);
    func_801C1ABC(6);
    func_801C1630();
}
