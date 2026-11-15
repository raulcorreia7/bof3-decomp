#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

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
            Message_StartAreaMessage(132);
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

#ifdef NON_MATCHING
NON_MATCHING void func_801FC380(void) {
    switch (g_SceneState.step_05) {
        case 0:
            func_801FC8A0(0x91);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            g_SceneState.step_05 = 2;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(37), TO_COORD(174), 0x8A);
                    break;
                case 2:
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(37), TO_COORD(174), 0x89);
                    break;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x1) {
                g_SceneState.step_05 = 3;
                SYS_SetFlag(g_SceneFlags, 0x30);
                g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(39), TO_COORD(173), 0x8C);
                        break;
                    case 2:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(39), TO_COORD(173), 0x8B);
                        break;
                }
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0xA) {
                g_SceneState.step_05 = 4;
                SYS_SetFlag(g_SceneFlags, 0x31);
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(34), TO_COORD(114), 0x8E);
                        break;
                    case 2:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(34), TO_COORD(114), 0x8D);
                        break;
                }
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x4) {
                g_SceneState.step_05 = 5;
                g_Characters[1].unk_07 |= 1;
                g_Characters[5].unk_07 |= 1;
                g_Characters[6].unk_07 |= 1;
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        Scene_RunScenario(3);
                        break;
                    case 2:
                        Scene_RunScenario(2);
                        break;
                }
            }
            break;
        case 5:
            if (g_GameStateIndex == 0) {
                g_ScriptVars[0]      = 0x5;
                g_SceneState.step_05 = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x5) {
                SYS_SetFlag(g_SceneFlags, 0x32);
                Game_ClearScriptActive();
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801FC380);
#endif

MATCH void func_801FC6A8(void) {
    u8* state;
    u8  next;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0:
            if (!(g_UiWindowChannel & FRONTEND_FLAG_CONFIRM)) {
                break;
            }
            next            = 1;
            g_ScriptVars[0] = next;
            SYS_SetFlag(g_SceneFlags, 0x3A);
            func_801BE1B0(3);
            Area_StartScrollRoute(0);
            *state = next;
            break;
        case 1:
            if (g_ScriptVars[0] != 0x1C) {
                break;
            }
            SYS_ClearFlag(g_SceneFlags, 0x3A);
            Game_ClearScriptActive();
            *state                = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}

MATCH void func_801FC778(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(76);
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

/* Give the lead party member a field actor of type 6: claim a free slot and seed its row from the member. */
MATCH void func_801FC8A0(s32 variant){ACTOR_SEED_PARTY_SLOT(0, D_801FD5C0, 6, variant + 112)}
#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FCA98(void) {
}

MATCH void func_801FCAA0(void) {
    if (SYS_TestFlag(g_SceneFlags, 2) == 0) {
        SYS_SetFlag(g_SceneFlags, 2U);
        Game_SetScriptActive();
        *g_ScriptVars = 0;
        D_80146865    = 0;
        D_80146866    = 0;
        D_80146867    = 0;
        D_80146875    = 0;
        D_80146874    = 0x15;
    }
}

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
    SCENE_ENTER_STATE_13();
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
    SCENE_ENTER_STATE_13();
}

MATCH s32 func_801FCD60(void) {
    return 0;
}

INCLUDE_ASM(func_801FCD68);

MATCH s8 func_801FD110(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FD668, 2, D_801FD674);
}

MATCH s32 func_801FD178(void) {
    SCENA05_START_SCENE(0x26, 1);
}

MATCH s32 func_801FD208(void) {
    SCENA05_START_SCENE(0x25, 0x19);
}

/* func_801FD298 */
MATCH void Scene_JoinMomoNinaPeco(void) {
    g_Characters[g_CharSlot[6]].unk_07 |= 1;
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
    Party_JoinMember(CHAR_ID_PECO);
}

/* func_801FD30C */
MATCH void Party_JoinNinaYoung(void) {
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
}

/* func_801FD32C */
MATCH void Party_JoinMomo(void) {
    Party_JoinMember(CHAR_ID_MOMO);
}

/* func_801FD34C */
MATCH void Party_JoinPeco(void) {
    Party_JoinMember(CHAR_ID_PECO);
}

/* func_801FD36C */
MATCH void Party_JoinRyuYoung(void) {
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
}

MATCH void func_801FD38C(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
}

/* func_801FD3C8 */
MATCH void Scene_JoinNinaYoung(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
}

MATCH void func_801FD404(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_PECO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_PECO);
}

/* func_801FD440 */
MATCH void Party_JoinGarr(void) {
    Party_JoinMember(CHAR_ID_GARR);
}

#include "overlays/scenario/Scene_JoinNina.h"

MATCH void Scene_JoinNina2(void) {
    SCENE_JOIN_NINA();
}

/* func_801FD4D8 */
MATCH void Scene_RemoveMomoNina(void) {
    Party_RemoveMember(CHAR_ID_MOMO);
    Party_RemoveMember(CHAR_ID_NINA_YOUNG);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RemoveNina.h"

#include "overlays/scenario/Scene_RemoveMomo.h"

#include "overlays/scenario/Scene_RemovePeco.h"

/* func_801FD580 */
MATCH void Scene_RemoveRyuYoung(void) {
    Party_RemoveMember(CHAR_ID_RYU_YOUNG);
    Party_LoadPalettes();
}
