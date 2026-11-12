#include "scena05_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F743C(void) {
    Actor* actor;

    actor              = g_Task;
    actor->vx          = 0;
    actor->header.mode = actor->header.mode + 1;
}

/* Hint: a3 is lhu of the low half of vx (0x0C), while 0x0C is also read as a word; the same field needs two widths. */
MATCH void func_801F745C(void) {
    Actor* work;

    work = g_Task;
    func_801F7660(work->pos.x.fixed, work->pos.y.fixed, work->pos.z.fixed, work->vx);
    g_Task->vx += 16;
    if (g_Task->vx > 1280) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F74CC(void) {
    Actor_Clear();
}

MATCH void func_801F74EC(void) {
    SYS_DISPATCH_TASK(D_801FD5B4, 1, g_Task);
}

MATCH void func_801F7530(void) {
    Actor* actor;

    actor              = g_Task;
    actor->vx          = 4096;
    actor->header.mode = actor->header.mode + 1;
}

MATCH void func_801F7554(void) {
    ActorSlot* spawned;
    Actor*     actor;
    u8         slot;

    if ((SP_REF(Actor*, 0x44)->vx & 0xF) == 0) {
        slot = Actor_FindFreeSlot();
        if (slot != GAME_NONE) {
            spawned               = &g_ActorSlots[slot];
            spawned->header.flags = 1;
            spawned->type         = 0x26;
            actor                 = g_Task;
            spawned->pos.x.fixed  = actor->pos.x.fixed;
            spawned->pos.y.fixed  = actor->pos.y.fixed;
            spawned->pos.z.fixed  = Area_SampleHeight(actor->pos.x.fixed, actor->pos.y.fixed) << 16;
        }
    }
    actor = g_Task;
    actor->vx -= 1;
    if (actor->vx == 0) {
        actor->header.mode += 1;
    }
}

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

MATCH void func_801F8430(void) {
    u8* step;

    step = &D_80146875;
    switch (*step) {
        case 0:
            Message_StartAreaMessage(5);
            g_GameStateIndex = 2;
            *step            = 1;
            break;
        case 1:
            if (g_GameStateIndex != 2) {
                D_80146866 = 1;
                *step      = 2;
                SYS_SetFlag(g_SceneFlags, 0);
                func_8019FA28(0x44, 0x1D0000, 0x1E0000, 0x80);
            }
            break;
        case 2:
            if (*g_ScriptVars == 0x2D) {
                SYS_SetFlag(g_SceneFlags, 1);
                Game_ClearScriptActive();
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                *step      = 0;
                D_80146874 = 0;
            }
            break;
    }
}

MATCH void func_801F8554(void) {
}

MATCH void func_801F855C(void) {
}

INCLUDE_ASM(func_801F8564);

INCLUDE_ASM(func_801F87C4);

MATCH void func_801F8B94(void) {
    if (g_SceneState.step_05 == 0) {
        if (g_ScriptVars[0] == 0x18) {
            SYS_SetFlag(g_SceneFlags, 10);
            Game_ClearScriptActive();
            D_80146865            = 0;
            D_80146866            = 0;
            D_80146867            = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
        }
    }
}

MATCH void func_801F8C1C(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(38);
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

MATCH void func_801F9148(void) {
    u8* step = &D_80146875;

    switch (*step) {
        case 0:
            if (*g_ScriptVars == 0x23) {
                *step = 1;
            }
            break;
        case 1:
            if (*g_ScriptVars == 0x23) {
                *step = 4;
                SYS_SetFlag(g_SceneFlags, 24);
                if (SYS_TestFlag(g_SceneFlags, 23) == 0) {
                    D_80146866 = 4;
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, 0x270000, 0xAD0000, FACING_RIGHT);
                    g_GamePrevSelection = 0xFF;
                }
                if (SYS_TestFlag(g_SceneFlags, 22) == 0) {
                    D_80146866 = 1;
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, 0x270000, 0xAD0000, 0x83);
                    g_GamePrevSelection = 0xFF;
                }
            }
            break;
        case 4:
            if (*g_ScriptVars == 3) {
                SYS_SetFlag(g_SceneFlags, 25);
                SYS_SetFlag(g_SceneFlags, 20);
                SYS_SetFlag(g_SceneFlags, 26);
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                Game_ClearScriptActive();
                *step      = 0;
                D_80146874 = 0;
            }
            break;
    }
}

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

INCLUDE_ASM(func_801FC380);

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
            func_801C601C(0);
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

INCLUDE_ASM(func_801FC8A0);

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
