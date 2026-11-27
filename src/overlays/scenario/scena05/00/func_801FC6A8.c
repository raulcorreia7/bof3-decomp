#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC6A8(void) {
    u8* state;
    u8  next;

    state = &g_ScenarioState.step;
    switch (*state) {
        case 0:
            if (!(g_UIWindowChannel & FRONTEND_FLAG_CONFIRM)) {
                break;
            }
            next            = 1;
            g_ScriptVars[0] = next;
            SYS_SetFlag(g_SceneFlags, 0x3A);
            Scene_SetupParty(3);
            Area_ScrollStartRoute(0);
            *state = next;
            break;
        case 1:
            if (g_ScriptVars[0] != 0x1C) {
                break;
            }
            SYS_ClearFlag(g_SceneFlags, 0x3A);
            Game_ClearScriptActive();
            *state                   = 0;
            g_ScenarioState.state_04 = 0;
            break;
    }
}

MATCH void func_801FC778(void) {
    u8* state;

    state = &g_ScenarioState.step;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(MSG_SCENA05_076);
            *state = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state                   = 0;
                g_ScenarioState.state_04 = 0;
            }
            return;
    }
}

MATCH void func_801FC808(void) {
    u8 i;

    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_MOMO) {
            g_ScriptVars[1] = 1;
        }
    }
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_PECO) {
            g_ScriptVars[1] = 2;
        }
    }
}

/* Give the lead party member a field actor of type 6: claim a free slot and seed its row from the member. */
MATCH void func_801FC8A0(s32 variant){ACTOR_SEED_PARTY_SLOT(0, D_801FD5C0, 6, variant + 112)}
#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH void func_801FCA98(void) {
}

MATCH void func_801FCAA0(void) {
    if (SYS_TestFlag(g_SceneFlags, 2) == 0) {
        SYS_SetFlag(g_SceneFlags, 2U);
        Game_SetScriptActive();
        *g_ScriptVars            = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 0x15;
    }
}

MATCH void func_801FCB1C(void) {
    SYS_SetFlag(g_SceneFlags, 11);
    Game_SetScriptActive();
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 8;
}

MATCH void func_801FCB80(void) {
    Game_SetScriptActive();
    SCRIPT_VARS_CLEAR_ALL();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 12;
}

MATCH void func_801FCBD4(void) {
    SCENE_ENTER_STATE_13();
}

MATCH void func_801FCC28(void) {
    Game_SetScriptActive();
    SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 16;
}

MATCH void func_801FCC74(void) {
    Game_SetScriptActive();
    SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 17;
}

MATCH void func_801FCCC0(void) {
    Game_SetScriptActive();
    SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 18;
}

MATCH void func_801FCD0C(void) {
    SCENE_ENTER_STATE_13();
}

MATCH s32 func_801FCD60(void) {
    return 0;
}

/* Start the scene script at the given state with its variables and first step cleared. */
#define SCENE_ENTER_STATE(state)     \
    Game_SetScriptActive();          \
    g_ScriptVars[0]          = 0;    \
    g_ScriptVars[1]          = 0;    \
    g_ScriptVars[2]          = 0;    \
    g_ScriptVars[3]          = 0;    \
    g_ScenarioState.step     = 0;    \
    g_ScenarioState.state_04 = state

MATCH s32 func_801FCD68(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_PLANT) {
        if (SYS_TestFlag(g_SceneFlags, 9) && SYS_TestFlag(g_SceneFlags, 11) == 0 && (x == TO_COORD(77) || x == TO_COORD_HALF(77)) && (u32)(y - TO_COORD(33)) <= TO_COORD_HALF(4)) {
            SCENE_ENTER_STATE(7);
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_DUMP) {
        if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
            if ((u32)(x - TO_COORD(147)) <= TO_COORD_HALF(1) && (y == TO_COORD(6) || y == TO_COORD_HALF(6))) {
                SCENE_ENTER_STATE(4);
                return 1;
            }
        } else if (SYS_TestFlag(g_SceneFlags, 9) == 0 && (u32)(x - TO_COORD(132)) <= TO_COORD_HALF(2) && (y == TO_COORD(12) || y == TO_COORD_HALF(12) || y == TO_COORD(24) || y == TO_COORD_HALF(24))) {
            Game_SetScriptActive();
            g_ScenarioState.step = 20;
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.state_04 = 4;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_MAEKYSS_GORGE && (y == TO_COORD(52) || y == TO_COORD_HALF(52)) && (u32)(x - TO_COORD(29)) <= TO_COORD_HALF(1)) {
        SCENE_ENTER_STATE(11);
        return 1;
    }
    if (g_GameAreaId == AREA_ID_CAFE) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0 && (y == TO_COORD(36) || y == TO_COORD_HALF(36)) && (u32)(x - TO_COORD(25)) <= TO_COORD_HALF(6)) {
            SCENE_ENTER_STATE(1);
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_CONTEST_OUTER && SYS_TestFlag(g_SceneFlags, 61)) {
        if (SYS_TestFlag(g_SceneFlags, 50) == 0) {
            if (x == TO_COORD_HALF(40) || x == TO_COORD(41)) {
                if ((u32)(y - TO_COORD(126)) <= TO_COORD_HALF(3)) {
                    SCENE_ENTER_STATE(19);
                    return 1;
                }
            } else if (x == TO_COORD(31) || x == TO_COORD_HALF(31)) {
                if ((u32)(y - TO_COORD(113)) <= TO_COORD_HALF(1)) {
                    SCENE_ENTER_STATE(20);
                    return 1;
                }
            }
        } else if ((x == TO_COORD(31) || x == TO_COORD_HALF(31)) && (u32)(y - TO_COORD(113)) <= TO_COORD_HALF(1)) {
            SCENE_ENTER_STATE(22);
            return 1;
        }
    }
    return 0;
}

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
    g_Characters[g_CharSlot[6]].party_flags |= PARTY_FLAG_JOINED;
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_MOMO);
    Party_MemberJoin(CHAR_ID_NINA_YOUNG);
    Party_MemberJoin(CHAR_ID_PECO);
}

/* func_801FD30C */
MATCH void Party_JoinNinaYoung(void) {
    Party_MemberJoin(CHAR_ID_NINA_YOUNG);
}

/* func_801FD32C */
MATCH void Party_JoinMomo(void) {
    Party_MemberJoin(CHAR_ID_MOMO);
}

/* func_801FD34C */
MATCH void Party_JoinPeco(void) {
    Party_MemberJoin(CHAR_ID_PECO);
}

/* func_801FD36C */
MATCH void Party_JoinRyuYoung(void) {
    Party_MemberJoin(CHAR_ID_RYU_YOUNG);
}

MATCH void func_801FD38C(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_MOMO);
}

/* func_801FD3C8 */
MATCH void Scene_JoinNinaYoung(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_NINA_YOUNG);
}

MATCH void func_801FD404(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_PECO, 0U);
    Party_BattlersBuild(PARTY_ORDER_FIELD);
    Party_MemberJoin(CHAR_ID_PECO);
}

/* func_801FD440 */
MATCH void Party_JoinGarr(void) {
    Party_MemberJoin(CHAR_ID_GARR);
}

#include "overlays/scenario/shared/Scene_JoinNina.h"

MATCH void Scene_JoinNina2(void) {
    SCENE_JOIN_NINA();
}

/* func_801FD4D8 */
MATCH void Scene_RemoveMomoNina(void) {
    Party_MemberRemove(CHAR_ID_MOMO);
    Party_MemberRemove(CHAR_ID_NINA_YOUNG);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_RemoveNina.h"

#include "overlays/scenario/shared/Scene_RemoveMomo.h"

#include "overlays/scenario/shared/Scene_RemovePeco.h"

/* func_801FD580 */
MATCH void Scene_RemoveRyuYoung(void) {
    Party_MemberRemove(CHAR_ID_RYU_YOUNG);
    Party_LoadPalettes();
}
