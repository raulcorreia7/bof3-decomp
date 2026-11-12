#include "scena06_00.h"
#include "area/spad.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchActor.h"

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
    SYS_SetFlag(g_SceneFlags, 12U);
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
    if (SYS_TestFlag(g_SceneFlags, 34) == 0) {
        D_80146875 = 0;
    } else {
        D_80146875 = 0x14;
    }
    D_80146874 = 0x10;
}

MATCH void func_801FD234(void) {
    Game_SetScriptActive();
    *g_ScriptVars = 0;
    D_80146865    = 0;
    if (SYS_TestFlag(g_SceneFlags, 35) != 0) {
        D_80146875 = 0x14;
    } else {
        D_80146875 = 0xA;
    }
    D_80146874 = 0x10;
}

MATCH s32 func_801FD294(void) {
    return 0;
}

MATCH void func_801FD29C(void) {
    D_80144DF8 = D_801FE464[0];
    D_80144DF2 = D_801FE464[6];
    D_80144DF5 = D_801FE464[7];
    D_80144E00 = D_801FE464[1];
    D_80144E20 = D_801FE464[1];
    D_80144E04 = D_801FE464[2];
    D_80144E24 = D_801FE464[2];
    D_80144E06 = D_801FE464[3];
    D_80144E26 = D_801FE464[3];
    D_80144E08 = D_801FE464[4];
    D_80144E28 = D_801FE464[4];
    D_80144E0A = D_801FE464[5];
    D_80144E2A = D_801FE464[5];
}

MATCH s8 func_801FD34C(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags) {
    return D_801FE46C[((Actor*)g_Task)->unk_04](entry, dir_x, dir_y, vz_start, vz_delta, landing_script, flags);
}

INCLUDE_ASM(func_801FD3BC);

INCLUDE_ASM(func_801FD568);

MATCH s8 func_801FD748(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags) {
    s16 distance;
    s16 z;

    distance = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    z        = COORD_INT(g_Task->pos.z);
    if (distance < z - 0x240) {
        COORD_INT(g_Task->pos.z) = z + (g_Task->vz >> 8);
        g_Task->vz += vz_delta;
        return 1;
    }
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) + 0x240;
    g_Task->unk_04           = 0;
    return 0;
}

INCLUDE_ASM(func_801FD800);

MATCH s8 func_801FDD14(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FE478, 4, D_801FE48C);
}

MATCH s32 func_801FDD7C(void) {
    if (Item_Count(1, 0x47, 0) == 0) {
        Game_SetScriptActive();
        g_ScriptVars[0]       = 0;
        g_ScriptVars[1]       = 0;
        g_ScriptVars[2]       = 0;
        g_ScriptVars[3]       = 0;
        g_SceneState.step_05  = 0;
        g_SceneState.state_04 = 0xB;
        return 1;
    }

    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 0xB;
    return 1;
}

MATCH void func_801FDE2C(void) {
}

MATCH s32 func_801FDE34(void) {
    if (!SYS_TestFlag(g_SceneFlags, 39)) {
        Game_SetScriptActive();
        g_ScriptVars[0]       = 0;
        g_ScriptVars[1]       = 0;
        g_ScriptVars[2]       = 0;
        g_ScriptVars[3]       = 0;
        g_SceneState.step_05  = 0;
        g_SceneState.state_04 = 0xD;
        return 1;
    }
    return 1;
}

INCLUDE_ASM(func_801FDEA4);

MATCH void func_801FDFFC(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

MATCH void func_801FE048(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

MATCH void func_801FE08C(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
    Party_LoadPalettes();
}

MATCH void func_801FE0D0(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

/* func_801FE11C */
MATCH void Party_JoinMomo(void) {
    Party_JoinMember(CHAR_ID_MOMO);
}

/* func_801FE13C */
MATCH void Party_JoinPeco(void) {
    Party_JoinMember(CHAR_ID_PECO);
}

#include "overlays/scenario/Scene_JoinNina.h"

MATCH void func_801FE198(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_GARR);
}

MATCH void Scene_JoinNina3(void) {
    SCENE_JOIN_NINA();
}

MATCH void func_801FE210(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
    Party_JoinMember(CHAR_ID_GARR);
}

/* func_801FE254 */
MATCH void Scene_RemoveRyuGarr(void) {
    Party_RemoveMember(CHAR_ID_RYU_YOUNG);
    Party_RemoveMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

/* func_801FE284 */
MATCH void Scene_RemoveRyuMomo(void) {
    Party_RemoveMember(CHAR_ID_RYU_YOUNG);
    Party_RemoveMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

/* func_801FE2B4 */
MATCH void Scene_RemoveRyuPeco(void) {
    Party_RemoveMember(CHAR_ID_RYU_YOUNG);
    Party_RemoveMember(CHAR_ID_PECO);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RemoveGarr.h"

#include "overlays/scenario/Scene_RemovePeco.h"

/* func_801FE334 */
MATCH void Scene_RemovePecoGarr(void) {
    Party_RemoveMember(CHAR_ID_PECO);
    Party_RemoveMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RemoveMomo.h"

/* func_801FE38C */
MATCH void Scene_RemoveMomoPeco(void) {
    Party_RemoveMember(CHAR_ID_MOMO);
    Party_RemoveMember(CHAR_ID_PECO);
    Party_LoadPalettes();
}
